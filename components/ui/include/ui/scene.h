#pragma once

#include <stdint.h>
#include <memory>

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>


namespace UI
{
  class GUI;

  enum class SceneId: uint8_t
  {
    None,
    Boot,
    PinRequest,
    PinVerify,
    Notify,
    Idle,
  };

  class SceneManager
  {
  public:
    esp_err_t Initialize();

    SceneId Id() const;
    void SwitchTo(SceneId sceneID);
    bool UpdateState();

  private:
    SceneId calcSceneLocked();

  private:
    SemaphoreHandle_t mu;
    SceneId curScene = SceneId::None;
    SceneId targetScene = SceneId::None;
    uint16_t idleTtlTicks = 0;
  };
}
