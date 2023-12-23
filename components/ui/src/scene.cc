#include <sdkconfig.h>
#include "ui/scene.h"

#include <esp_log.h>

#include <defer.h>


using namespace UI;

namespace
{
  static const char* TAG = "ui::scene";
}

esp_err_t SceneManager::Initialize()
{
  mu = xSemaphoreCreateMutex();
  if (mu == nullptr) {
    ESP_LOGE(TAG, "unable to allocate mutex");
    return ESP_ERR_NO_MEM;
  }

  return ESP_OK;
}

SceneId SceneManager::Id() const
{
  return curScene;
}

void SceneManager::SwitchTo(SceneId sceneID)
{
  if (xSemaphoreTake(mu, portMAX_DELAY) == pdFALSE) {
    ESP_LOGE(TAG, "unable to get scene lock");
    return;
  }
  REF_DEFER(xSemaphoreGive(mu));

  if (curScene != targetScene) {
    ESP_LOGW(TAG,
      "switch to screen with skips: %d -> %d (skip) -> %d",
      (int)curScene,
      (int)targetScene,
      (int)sceneID
    );
  }

  curScene = SceneId::None;
  targetScene = sceneID;
}

bool SceneManager::UpdateState()
{
  if (xSemaphoreTake(mu, portMAX_DELAY) == pdFALSE) {
    ESP_LOGE(TAG, "unable to get scene lock");
    return false;
  }
  REF_DEFER(xSemaphoreGive(mu));

  SceneId newSceneID = calcSceneLocked();
  if (newSceneID == curScene) {
    return false;
  }

  curScene = newSceneID;
  return true;
}

SceneId SceneManager::calcSceneLocked()
{
  if (idleTtlTicks > 0) {
    idleTtlTicks--;
  }

  if (curScene == targetScene) {
    if (curScene != SceneId::Notify || idleTtlTicks > 0) {
      return curScene;
    }

    ESP_LOGI(TAG, "switch to idle screen by TTL");
    targetScene = SceneId::Idle;
  }

  idleTtlTicks = (CONFIG_UI_SCENE_IDLE_TTL_MS /CONFIG_UI_PERIOD_TIME_MS);
  return targetScene;
}
