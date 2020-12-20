#include "CVocab.h"

void CVocab::OnEvent(SDL_Event* Event) {
  if (CTransition::control.isActive()) return;

  CEvent::OnEvent(Event);
}

void CVocab::OnKeyDown(SDL_Keycode sym, Uint16 mod) {

}

void CVocab::OnLButtonDown(int mX, int mY) {
  using namespace vocab;
  const SDL_Point p = {mX, mY};

  if (at_menu) {
    for (int i = 0; i <= GROUP_BY_ALPHA; i++) {
      if (SDL_PointInRect(&p, &r_options[i])) {
        group_option = i;
        at_menu = false;
        break;
      }
    }
  } else {

  }
}
