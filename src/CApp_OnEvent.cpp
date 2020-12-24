#include "CApp.h"

void CApp::OnEvent(SDL_Event* Event) {
  switch(*active_mode) {
    case APP_MODE_TITLE: CTitle::control.OnEvent(Event); break;
    case APP_MODE_LESSON: break;
    case APP_MODE_VOCAB: CVocab::control.OnEvent(Event); break;
    case APP_MODE_GRAMMAR: break;
    case APP_MODE_PRACTICE: break;
    case APP_MODE_NEW: CCreate::control.OnEvent(Event); break;
    case APP_MODE_STATS: break;
    case APP_MODE_OPTIONS: break;
  }

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
