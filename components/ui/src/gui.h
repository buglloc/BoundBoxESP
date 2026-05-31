#pragma once

#include <functional>
#include <string>

#include <lvgl.h>

#include "ui/manager.h"


namespace UI
{
  class GUI
  {
  public:
    GUI();
    void ShowScreenPinEnter();
    void ShowScreenPinVerify(const std::string& verification);
    void ShowScreenNotification(const std::string& msg);
    void ShowInfoScreen();
    void SetPinPromptHandler(std::function<void(int8_t)> handler);
    void UpdateNotification(const char* msg);
    void UpdateBoardState(BoardState state);
    void UpdateLocalAddr(uint32_t addr);
    void UpdateAssertations(uint32_t assertations);
    void UpdateCoreTemp(uint32_t temp);
    void UpdateBattVoltage(uint32_t voltage);

    ~GUI();
  private:
    lv_obj_t* createPage(lv_obj_t *screen);
    lv_obj_t* switchScreen(lv_obj_t *targetScreen);
    bool isPersistentScreen(lv_obj_t* scr);

  private:
    lv_obj_t* notifyScreen = nullptr;
    lv_obj_t* infoScreen = nullptr;
    lv_obj_t* notifyLabel = nullptr;
    lv_obj_t* stateLabel = nullptr;
    lv_obj_t* ipLabel = nullptr;
    lv_obj_t* assesLabel = nullptr;
    lv_obj_t* tempLabel = nullptr;
    lv_obj_t* battLabel = nullptr;
    std::function<void(int8_t)> pinPromptHandler;
  };
}
