#include "CApp.h"

void CApp::OnEvent(SDL_Event* Event) {
  // if (CMode::isFlagOn(APP_MODE_GAME)) {
  //   // Process events during gameplay
  //   CGame::control.OnEvent(Event);
  // } else if (CMode::isFlagOn(APP_MODE_TITLE)) {
  //   // Process events at title screen
  //   CTitle::control.OnEvent(Event);
  //   if (CTitle::control.call_terminate) Running = false;
  // } else if (CMode::isFlagOn(APP_MODE_FATAL)) {
  //   // Process events during a fatal error
  // }
  CEvent::OnEvent(Event);
}


void CApp::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
  switch (sym) {
    case SDLK_ESCAPE: {
      if (!esc_init) esc_init = SDL_GetTicks();
      break;
    }
    default: break;
  }
}

void CApp::OnKeyUp(SDL_Keycode sym, Uint16 mod) {
  switch (sym) {
    case SDLK_ESCAPE: esc_init = false; break;
    default: break;
  }
}

void CApp::OnExit() {
  Running = false;
}
