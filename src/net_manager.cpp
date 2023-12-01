#include "board_config.h"
#include "net_manager.h"

#include <SPI.h>
#include <ArduinoLog.h>
#ifdef NET_HAVE_ETHERNET
#include <Ethernet.h>
#endif

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

bool TNetManager::Begin(const String& hostname, const TNetConfig& cfg)
{
  Log.infoln("network manager starts");

  bool ok = false;
  switch (cfg.Kind) {
#ifdef NET_HAVE_ETHERNET
    case NetKind::Ethernet:
      impl = new TEthernetNetManager();
      ok = impl->Begin(hostname, cfg);
      break;
#endif
#ifdef NET_HAVE_WIFI
    case NetKind::WiFi:
      impl = new TWiFiNetManager();
      ok = impl->Begin(hostname, cfg);
      break;
#endif
    default:
      Log.errorln("no net configured - nothing to do");
      return false;
  }

  Log.infoln("network setup complete");
  return ok;
}

cpp::result<TNetConfig&, TNetConfig::MarshalErr> TNetConfig::FromJson(const JsonObjectConst& obj) noexcept
{
  TNetConfig cfg;
  // some defaults
  cfg.Kind = NetKind::WiFi;
  fillMac(cfg.Mac);

  if (obj.isNull() || !obj.containsKey("kind")) {
    // that's fine
    return cfg;
  }

  String kind = obj["kind"];
  if (kind == "wifi") {
    cfg.Kind = NetKind::WiFi;
  } else if (kind == "ethernet") {
    cfg.Kind = NetKind::Ethernet;
  } else {
    Log.errorln("net config: unexpected net kind: %s", kind);
    return cpp::fail(TNetConfig::MarshalErr::ShitHappens);
  }

  if (fillAddress(obj["ip"].as<String>(), &cfg.IP)) {
    Log.errorln("net config: invalid ip: %s", obj["ip"]);
    return cpp::fail(TNetConfig::MarshalErr::ShitHappens);
  }

  if (fillAddress(obj["subnet"].as<String>(), &cfg.Subnet)) {
    Log.errorln("net config: invalid subnet: %s", obj["subnet"]);
    return cpp::fail(TNetConfig::MarshalErr::ShitHappens);
  }

  if (fillAddress(obj["dns"].as<String>(), &cfg.DNS)) {
    Log.errorln("net config: invalid dns: %s", obj["dns"]);
    return cpp::fail(TNetConfig::MarshalErr::ShitHappens);
  }

  if (fillAddress(obj["gateway"].as<String>(), &cfg.Gateway)) {
    Log.errorln("net config: invalid gateway: %s", obj["gateway"]);
    return cpp::fail(TNetConfig::MarshalErr::ShitHappens);
  }

  int macFields = sscanf(
    obj["mac"].as<String>().c_str(),
    "%2hhx:%2hhx:%2hhx:%2hhx:%2hhx:%2hhx",
    &cfg.Mac[0], &cfg.Mac[1], &cfg.Mac[2], &cfg.Mac[3], &cfg.Mac[4], &cfg.Mac[5]
  );
  if (macFields != 6) {
    Log.errorln("net config: invalid mac: %s", obj["mac"]);
    return cpp::fail(TNetConfig::MarshalErr::ShitHappens);
  }

  return cfg;
}

cpp::result<JsonObject, TNetConfig::MarshalErr> TNetConfig::ToJson() noexcept {
  StaticJsonDocument<1024> obj;
  switch (Kind) {
  case NetKind::WiFi:
    obj["kind"] = "wifi";
    break;

  case NetKind::Ethernet:
    obj["kind"] = "ethernet";
    break;

  default:
    return obj.as<JsonObject>();
  }

  if (IP != IPAddressNone) {
    obj["ip"] = IP.toString();
  }

  if (Subnet != IPAddressNone) {
    obj["subnet"] = Subnet.toString();
  }

  if (DNS != IPAddressNone) {
    obj["dns"] = DNS.toString();
  }

  if (Gateway != IPAddressNone) {
    obj["gateway"] = Gateway.toString();
  }

  char macBuf[17];
  sprintf(
    macBuf,
    "%2hhx:%2hhx:%2hhx:%2hhx:%2hhx:%2hhx",
    Mac[0], Mac[1], Mac[2], Mac[3], Mac[4], Mac[5]
  );
  macBuf[17] = '\0';
  obj["mac"] = String(macBuf);

  return obj.as<JsonObject>();
}

#ifdef NET_HAVE_ETHERNET
bool TEthernetNetManager::Begin(const String& hostname, const TNetConfig& cfg)
{
  Log.infoln(
    "setup ethernet network (SS: %d, SCK: %d, MISO: %d, MOSI: %d)",
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
    Log.errorln("ethernet phy was not found.  Sorry, can't run without hardware. :(");
    return false;
  }

  while (Ethernet.linkStatus() != LinkON) {
    Log.infoln("ethernet cable is not connected. waiting...");
    delay(100); // do nothing, no point running without Ethernet hardware
  }

  Log.infoln("ethernet network initialized (Local IP: %s)", Ethernet.localIP().toString());
  return true;
}

void TEthernetNetManager::Tick()
{
}

IPAddress TEthernetNetManager::LocalIP()
{
  return Ethernet.localIP();
}
#endif

#ifdef NET_HAVE_WIFI
bool TWiFiNetManager::Begin(const String& hostname, const TNetConfig& cfg)
{
  Log.infoln("setup wifi manager");
  if (cfg.IP != INADDR_NONE) {
    wifiManager.setSTAStaticIPConfig(cfg.IP, cfg.Gateway, cfg.Subnet);
  }
  esp_wifi_set_mac(WIFI_IF_STA, cfg.Mac);
  wifiManager.setHostname(hostname);

  wifiManager.setDebugOutput(true);
  wifiManager.setConnectTimeout(NET_WIFI_CONNECT_TIMEOUT);
  wifiManager.setAPCallback([&hostname](WiFiManager *myWiFiManager) {
    Log.infoln("entered config mode. SSID: %s", hostname);
  });

  if (!wifiManager.autoConnect(hostname.c_str(), nullptr)) {
    Log.errorln("unable to setup wifi");
    return false;
  }

  Log.infoln("ethernet network initialized (Local IP: %s)", WiFi.localIP().toString());
  return true;
}

void TWiFiNetManager::Tick()
{
}

IPAddress TWiFiNetManager::LocalIP()
{
  return WiFi.localIP();
}
#endif
