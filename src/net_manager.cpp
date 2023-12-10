#include "board_config.h"
#include "net_manager.h"

#include <SPI.h>
#include <ArduinoLog.h>
#ifdef NET_HAVE_ETHERNET
#include <Ethernet.h>
#endif

#define LOG_PREFIX "net_manager: "

namespace
{
  static IPAddress IPAddressNone(0, 0, 0, 0);

  void fillMac(uint8_t* mac)
  {
    esp_fill_random(mac, 6);
    mac[0] = 0xDE;
    mac[1] = 0xAD;
  }

  bool fillAddress(const String& in, IPAddress* out)
  {
    if (in.isEmpty()) {
      return true;
    }

    return out->fromString(in);
  }
}

TNetManager& TNetManager::Instance()
{
  static TNetManager instance;
  return instance;
}

bool TNetManager::Begin(NetKind kind)
{
  Log.infoln(LOG_PREFIX "starts");

  switch (kind) {
#ifdef NET_HAVE_ETHERNET
    case NetKind::Ethernet:
      impl = new TEthernetNetManager();
      break;
#endif
#ifdef NET_HAVE_WIFI
    case NetKind::WiFi:
      impl = new TWiFiNetManager();
      break;
#endif
    default:
      Log.errorln(LOG_PREFIX "no net configured - nothing to do");
      return false;
  }

  Log.infoln(LOG_PREFIX "setup complete");
  return true;
}

cpp::result<std::unique_ptr<TNetConfig>, TNetConfig::MarshalErr> TNetConfig::FromJson(const JsonObjectConst& obj) noexcept
{
  std::unique_ptr<TNetConfig> cfg(new TNetConfig());

  String kind = obj["kind"] | "default";
  if (kind == "wifi") {
    cfg->Kind = NetKind::WiFi;

  } else if (kind == "ethernet") {
    cfg->Kind = NetKind::Ethernet;

  } else if (kind == "default") {
    cfg->Kind = NetKind::WiFi;
    fillMac(cfg->Mac);
    return cfg;

  } else {
    Log.errorln(LOG_PREFIX "unexpected net kind: %s", kind);
    return cpp::fail(TNetConfig::MarshalErr::ShitHappens);
  }

  if (fillAddress(obj["ip"].as<String>(), &cfg->IP)) {
    Log.errorln(LOG_PREFIX "invalid ip: %s", obj["ip"]);
    return cpp::fail(TNetConfig::MarshalErr::ShitHappens);
  }

  if (fillAddress(obj["subnet"].as<String>(), &cfg->Subnet)) {
    Log.errorln(LOG_PREFIX "invalid subnet: %s", obj["subnet"]);
    return cpp::fail(TNetConfig::MarshalErr::ShitHappens);
  }

  if (fillAddress(obj["dns"].as<String>(), &cfg->DNS)) {
    Log.errorln(LOG_PREFIX "invalid dns: %s", obj["dns"]);
    return cpp::fail(TNetConfig::MarshalErr::ShitHappens);
  }

  if (fillAddress(obj["gateway"].as<String>(), &cfg->Gateway)) {
    Log.errorln(LOG_PREFIX "invalid gateway: %s", obj["gateway"]);
    return cpp::fail(TNetConfig::MarshalErr::ShitHappens);
  }

  int macFields = sscanf(
    obj["mac"].as<String>().c_str(),
    "%2hhx:%2hhx:%2hhx:%2hhx:%2hhx:%2hhx",
    &cfg->Mac[0], &cfg->Mac[1], &cfg->Mac[2], &cfg->Mac[3], &cfg->Mac[4], &cfg->Mac[5]
  );
  if (macFields != 6) {
    Log.errorln(LOG_PREFIX "invalid mac: %s", obj["mac"]);
    return cpp::fail(TNetConfig::MarshalErr::ShitHappens);
  }

  return cfg;
}

cpp::result<void, TNetConfig::MarshalErr> TNetConfig::ToJson(JsonObject& out) const noexcept
{
  switch (Kind) {
    case NetKind::WiFi:
      out["kind"] = "wifi";
      break;

    case NetKind::Ethernet:
      out["kind"] = "ethernet";
      break;

    default:
      return {};
  }

  if (IP != IPAddressNone) {
    out["ip"] = IP.toString();
  }

  if (Subnet != IPAddressNone) {
    out["subnet"] = Subnet.toString();
  }

  if (DNS != IPAddressNone) {
    out["dns"] = DNS.toString();
  }

  if (Gateway != IPAddressNone) {
    out["gateway"] = Gateway.toString();
  }

  char macBuf[17];
  sprintf(
    macBuf,
    "%2hhx:%2hhx:%2hhx:%2hhx:%2hhx:%2hhx",
    Mac[0], Mac[1], Mac[2], Mac[3], Mac[4], Mac[5]
  );
  macBuf[17] = '\0';
  out["mac"] = String(macBuf);

  return {};
}

#ifdef NET_HAVE_ETHERNET
bool TEthernetNetManager::Connect(const String& hostname, const TNetConfig& cfg)
{
  Log.infoln(
    LOG_PREFIX "setup ethernet network (SS: %d, SCK: %d, MISO: %d, MOSI: %d)",
    NET_ETHERNET_SS_PIN, SCK, MISO, MOSI
  );

  Ethernet.init(NET_ETHERNET_SS_PIN);
  uint8_t mac = cfg.Mac[0];
  if (cfg.IP == INADDR_NONE) {
    Ethernet.begin(&mac);
  } else {
    Ethernet.begin(&mac, cfg.IP, cfg.DNS, cfg.Gateway, cfg.Subnet);
  }

  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Log.errorln(LOG_PREFIX "ethernet phy was not found.  Sorry, can't run without hardware. :(");
    return false;
  }

  while (Ethernet.linkStatus() != LinkON) {
    Log.infoln(LOG_PREFIX "ethernet cable is not connected. waiting...");
    delay(100); // do nothing, no point running without Ethernet hardware
  }

  Log.infoln(LOG_PREFIX "ethernet network initialized (Local IP: %p)", Ethernet.localIP());
  return true;
}

IPAddress TEthernetNetManager::LocalIP()
{
  return Ethernet.localIP();
}
#endif

#ifdef NET_HAVE_WIFI
bool TWiFiNetManager::Connect(const String& hostname, const TNetConfig& cfg)
{
  Log.infoln(LOG_PREFIX "setup wifi manager");
  if (cfg.IP != INADDR_NONE) {
    wifiManager.setSTAStaticIPConfig(cfg.IP, cfg.Gateway, cfg.Subnet);
  }
  esp_wifi_set_mac(WIFI_IF_STA, cfg.Mac);
  wifiManager.setHostname(hostname);

  wifiManager.setDebugOutput(true);
  wifiManager.setConnectTimeout(NET_WIFI_CONNECT_TIMEOUT);
  wifiManager.setAPCallback([&hostname](WiFiManager *myWiFiManager) {
    Log.infoln(LOG_PREFIX "entered config mode. SSID: %s", hostname);
  });

  if (!wifiManager.autoConnect(hostname.c_str(), nullptr)) {
    Log.errorln(LOG_PREFIX "unable to setup wifi");
    return false;
  }

  Log.infoln(LOG_PREFIX "wifi network initialized (Local IP: %p)", WiFi.localIP());
  return true;
}

IPAddress TWiFiNetManager::LocalIP()
{
  return WiFi.localIP();
}
#endif
