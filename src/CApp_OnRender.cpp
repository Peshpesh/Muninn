#include "CApp.h"

void CApp::OnRender() {
  static bool DEBUG = true;

  CSurface::Clear();

  // if (CMode::isFlagOn(APP_MODE_GAME)) {
  //   CGame::control.OnRender();
  // } else if (CMode::isFlagOn(APP_MODE_TITLE)) {
  //   CTitle::control.OnRender();
  // }  else if (CMode::isFlagOn(APP_MODE_FATAL)) {
  //   //
  // }

  if (!CTransition::control.OnRender()) {
    // ERROR
  }

  // if (DEBUG) {
  //   std::string fps_str = CUtil::intToStr(CFPS::FPSControl.GetFPS()) + " fps";
  //   std::string speedfactor_str = CUtil::doubleToStr(CFPS::FPSControl.GetSpeedFactor(),10) + " SF";
  //   const SDL_Point fps_pos = {1,1};
  //   const SDL_Point sf_pos = {100,1};
  //   CType::Write(FONT_MINI, fps_str.c_str(), fps_pos, &rgb::white);
  //   CType::Write(FONT_MINI, speedfactor_str.c_str(), sf_pos, &rgb::white);
  // }

  if (esc_init) drawQuitMsg();

  CSurface::Present();
}

void CApp::drawQuitMsg() {
  using namespace gen;
  int msg_A = ((double)(SDL_GetTicks() - esc_init) / ESC_THRESH) * MAX_RGBA;
  if (CType::control.SetOpacity(msg_A)) {
    CType::Write(quit_msg_f, quit_msg, quit_msg_p, quit_msg_c);
  }
  CType::control.SetOpacity(MAX_RGBA);
}
