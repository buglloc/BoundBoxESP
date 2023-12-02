#ifndef BB_NET_MANAGER_H
#define BB_NET_MANAGER_H

#include "board_config.h"

#include <Result.h>
#include <ArduinoJson.h>
#include <IPAddress.h>
#ifdef NET_HAVE_WIFI
#include <WiFiManager.h>
#endif

enum class NetKind
{
  WiFi,
  Ethernet,
};

struct TNetConfig
{
  NetKind Kind;
  IPAddress IP;
  IPAddress Subnet;
  IPAddress DNS;
  IPAddress Gateway;
  uint8_t Mac[6];

  enum class MarshalErr
  {
    None,
    ShitHappens
  };

  static cpp::result<std::unique_ptr<TNetConfig>, MarshalErr> FromJson(const JsonObjectConst& obj) noexcept;
  cpp::result<void, MarshalErr> ToJson(JsonObject& out) const noexcept;
};

class INetImpl
{
public:
  virtual bool Begin(const String& hostname, const TNetConfig& cfg) = 0;
  virtual void Tick() = 0;
  virtual IPAddress LocalIP() = 0;
};

class TNetManager
{
public:
  static TNetManager &Instance();

  bool Begin(const String& hostname, const TNetConfig& cfg);

  void Tick()
  {
    impl->Tick();
  }

  IPAddress LocalIP()
  {
    return impl->LocalIP();
  }

private:
  TNetManager() = default;
  ~TNetManager()
  {
    delete impl;
    impl = nullptr;
  }

private:
  INetImpl* impl = nullptr;
};

#ifdef NET_HAVE_ETHERNET
class TEthernetNetManager final: public INetImpl
{
public:
  TEthernetNetManager() = default;
  bool Begin(const String& hostname, const TNetConfig& cfg) override;
  void Tick() override;
  IPAddress LocalIP() override;
};
#endif

#ifdef NET_HAVE_WIFI
class TWiFiNetManager final: public INetImpl
{
public:
  TWiFiNetManager() = default;
  bool Begin(const String& hostname, const TNetConfig& cfg) override;
  void Tick() override;
  IPAddress LocalIP() override;
private:
  WiFiManager wifiManager;
};
#endif

#endif