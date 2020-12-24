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

void CTitle::OnLButtonDown(int mX, int mY) {
  using namespace title;

  const SDL_Point p = {mX, mY};

  if (SDL_PointInRect(&p, &r_lesson)) {
    transMode = new app_module;
    *transMode = APP_MODE_LESSON;
    CTransition::control.reqTrans(TRANS_WIPE, c_lesson);
  }
  else if (SDL_PointInRect(&p, &r_vocab)) {
    transMode = new app_module;
    *transMode = APP_MODE_VOCAB;
    CTransition::control.reqTrans(TRANS_WIPE, c_vocab);
  }
  else if (SDL_PointInRect(&p, &r_grammar)) {
    transMode = new app_module;
    *transMode = APP_MODE_GRAMMAR;
    CTransition::control.reqTrans(TRANS_WIPE, c_grammar);
  }
  else if (SDL_PointInRect(&p, &r_practice)) {
    transMode = new app_module;
    *transMode = APP_MODE_PRACTICE;
    CTransition::control.reqTrans(TRANS_WIPE, c_practice);
  }
  else if (SDL_PointInRect(&p, &r_add)) {
    transMode = new app_module;
    *transMode = APP_MODE_NEW;
    CTransition::control.reqTrans(TRANS_WIPE, c_add);
  }
  else if (SDL_PointInRect(&p, &r_stats)) {
    transMode = new app_module;
    *transMode = APP_MODE_STATS;
    CTransition::control.reqTrans(TRANS_WIPE, c_stats);
  }
}
