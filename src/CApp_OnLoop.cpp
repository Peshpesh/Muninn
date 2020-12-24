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

  switch(*active_mode) {
    case APP_MODE_TITLE: CTitle::control.OnLoop(); break;
    case APP_MODE_LESSON: break;
    case APP_MODE_VOCAB: break;
    case APP_MODE_GRAMMAR: break;
    case APP_MODE_PRACTICE: break;
    case APP_MODE_NEW: CCreate::control.OnLoop(cursor); break;
    case APP_MODE_STATS: break;
    case APP_MODE_OPTIONS: break;
  }

  if (CTransition::control.isActive()) {
    CTransition::control.OnLoop();
  }

  CFPS::FPSControl.OnLoop();

  if (esc_init && (SDL_GetTicks() - esc_init) >= ESC_THRESH) {
    // call to terminate game
    Running = false;
  }
}
