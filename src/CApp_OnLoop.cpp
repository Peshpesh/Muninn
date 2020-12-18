#include "CApp.h"

void CApp::OnLoop() {
  // if (CMode::isFlagOn(APP_MODE_GAME)) {
  //   CGame::control.OnLoop();
  //   if (CMode::isFlagOn(APP_MODE_TITLE)) {
  //     // switch from Game to Title
  //     CGame::control.OnExit();
  //     CTitle::control.OnInit();
  //   }
  // } else if (CMode::isFlagOn(APP_MODE_TITLE)) {
  //   CTitle::control.OnLoop();
  //   if (CMode::isFlagOn(APP_MODE_GAME)) {
  //     // switching from Title to Game
  //     if (!CGame::control.OnInit()) {
  //       // ERROR COULD NOT INITIALIZE GAME
  //     }
  //   }
  // } else if (CMode::isFlagOn(APP_MODE_FATAL)) {
  //   //
  // }

  SDL_GetMouseState(&cursor.x, &cursor.y);

  CFPS::FPSControl.OnLoop();

  if (esc_init && (SDL_GetTicks() - esc_init) >= ESC_THRESH) {
    // call to terminate game
    Running = false;
  }
}
