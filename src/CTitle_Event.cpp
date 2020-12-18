#include "CTitle.h"

void CTitle::OnEvent(SDL_Event* Event) {
  if (CTransition::control.isActive()) return;

  // if (CControls::handler.con_change != CON_NONE) {
  //   CControls::handler.OnEvent(Event);
  //   return;
  // } else if (CConfig::control.con_change != CONFIG_NONE) {
  //   CConfig::control.OnEvent(Event);
  //   return;
  // }
  CEvent::OnEvent(Event);
}

void CTitle::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
  // Gamecon action = CControls::handler.getAction(sym, mod);
  //
  // if (action != CON_NONE) {
  //   switch (menu_kind) {
  //     case Title::MAIN:       eventTitle(action); break;
  //     case Title::NEW_GAME:   eventNewGame(action);  break;
  //     case Title::LOAD_GAME:  eventLoadGame(action); break;
  //     case Title::OPTIONS:    eventOptions(action);  break;
  //     default: break;
  //   }
  // }
}
