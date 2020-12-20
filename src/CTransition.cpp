#include "CTransition.h"

CTransition CTransition::control;

CTransition::CTransition() {
  okToTrans = false;
  init_reset_time = 250;
  init_delay_time = 300;
  fadeout_timer = fadein_timer = delay_timer = last_time = 0;
  color = &palette::red;
  transtype = TRANS_WIPE;
}

void CTransition::reqTrans(const int& transtype, const SDL_Point* palcol) {
  if (color) this->color = color;
  this->transtype = transtype;

  fadeout_timer = fadein_timer = init_reset_time;
  delay_timer   = init_delay_time;
  last_time     = SDL_GetTicks();
}

void CTransition::reqReset() {
  fadeout_timer = fadein_timer = init_reset_time;
  delay_timer   = init_delay_time;
  last_time     = SDL_GetTicks();
}

bool CTransition::isActive() {
  return (fadeout_timer || fadein_timer || delay_timer);
}

void CTransition::transDone() {
  okToTrans = false;
}

void CTransition::OnLoop() {
  if (fadeout_timer) {
    fadeout_timer -= (SDL_GetTicks() - last_time);
    last_time = SDL_GetTicks();
    if (fadeout_timer <= 0) {
      fadeout_timer = 0;
      okToTrans = true;
    }
  } else if (delay_timer) {
    if (!okToTrans) {
      delay_timer -= (SDL_GetTicks() - last_time);
      if (delay_timer < 0) delay_timer = 0;
    }
    last_time = SDL_GetTicks();
  } else if (fadein_timer) {
    fadein_timer -= (SDL_GetTicks() - last_time);
    if (fadein_timer < 0) fadein_timer = 0;
    last_time = SDL_GetTicks();
  }
}

void CTransition::OnRender() {
  if (fadeout_timer) wipeout();
  else if (delay_timer) blank();
  else if (fadein_timer) wipein();
}

void CTransition::wipeout() {
  // left-to-right wipe (TO color)
  int w = ((float)(WWIDTH * (init_reset_time - fadeout_timer)) / init_reset_time);
  SDL_Rect fill = {0, 0, w, WHEIGHT};
  CAsset::drawBoxFill(fill, color);
}

void CTransition::blank() {
  // blank screen between fades
  SDL_Rect fill = {0, 0, WWIDTH, WHEIGHT};
  CAsset::drawBoxFill(fill, color);
}

void CTransition::wipein() {
  // left-to-right wipe (FROM color)
  int w = ((float)(WWIDTH * fadein_timer) / init_reset_time);
  SDL_Rect fill = {WWIDTH - w, 0, w, WHEIGHT};
  CAsset::drawBoxFill(fill, color);
}
