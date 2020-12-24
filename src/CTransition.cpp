#include "CTransition.h"

CTransition CTransition::control;

CTransition::CTransition() {
  okToTrans = false;
  init_reset_time = 800;
  init_delay_time = 600;
  fadeout_timer = fadein_timer = delay_timer = last_time = 0;
  color = &palette::red;
  transtype = TRANS_WIPE;
}

bool CTransition::OnInit() {
  return transMask.initCanvas(WWIDTH, WHEIGHT);
}

void CTransition::reqTrans(const int& transtype, const SDL_Point* palcol) {
  if (color) this->color = palcol;
  this->transtype = transtype;

  transMask.clearCanvas();

  fadeout_timer = fadein_timer = init_reset_time;
  delay_timer   = init_delay_time;
  last_time     = SDL_GetTicks();
}

void CTransition::reqReset() {
  transMask.clearCanvas();

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
  if (fadeout_timer) checkerout(); //wipeout();
  else if (delay_timer) blank();
  else if (fadein_timer) checkerin(); //wipein();
}

void CTransition::blank() {
  // blank screen between fades
  SDL_Rect fill = {0, 0, WWIDTH, WHEIGHT};
  CAsset::drawBoxFill(fill, color);
}

void CTransition::wipeout() {
  // left-to-right wipe (TO color)
  int w = ((float)(WWIDTH * (init_reset_time - fadeout_timer)) / init_reset_time);
  SDL_Rect fill = {0, 0, w, WHEIGHT};
  CAsset::drawBoxFill(fill, color);
}

void CTransition::wipein() {
  // left-to-right wipe (FROM color)
  int w = ((float)(WWIDTH * fadein_timer) / init_reset_time);
  SDL_Rect fill = {WWIDTH - w, 0, w, WHEIGHT};
  CAsset::drawBoxFill(fill, color);
}

void CTransition::checkerout() {
  static const int max_W = 64;
  static const int cols = (WWIDTH / max_W)  + (bool)(max_W % WWIDTH);
  static const int rows = (WHEIGHT / max_W) + (bool)(max_W % WHEIGHT);
  static const int frag_wave_t = init_reset_time / 3; // time to initialize all fragments
  static const int frag_anim_t = init_reset_time - frag_wave_t; // time to complete a fragment animation
  static const int max_angle = 180;

  transMask.clearCanvas();
  transMask.beginDrawing();

  int t_elapsed = init_reset_time - fadeout_timer;
  int Xo = -(max_W % WWIDTH)  / 2;
  int Yo = -(max_W % WHEIGHT) / 2;
  int col_init_dt = frag_wave_t / (cols - 1); // time between fragment inits for a column
  int row_init_dt = frag_wave_t / (rows - 1); // time between fragment inits for a row

  SDL_Rect frag;
  for (int i = 0; i < cols; i++) {
    for (int j = 0; j < rows; j++) {
      int col_init_t = i * col_init_dt;        // t_elapsed when this column inits
      if (!(t_elapsed > col_init_t)) break;    // equiv not needed as W = 0, nothing to render
      int row_init_t = j * row_init_dt;        // t_elapsed when this row inits
      if (!(t_elapsed > row_init_t)) continue; // equiv not needed as W = 0, nothing to render

      int frag_t = (col_init_t < row_init_t) ? t_elapsed - col_init_t           : t_elapsed - row_init_t;
      int sz     = (frag_t < frag_anim_t)    ? max_W * frag_t / frag_anim_t     : max_W;
      int angle  = (frag_t < frag_anim_t)    ? max_angle * frag_t / frag_anim_t : max_angle;

      sz -= (sz % 2);
      frag.w = frag.h = sz;
      frag.x = Xo + (i * max_W) + ((max_W - sz) / 2);
      frag.y = Yo + (j * max_W) + ((max_W - sz) / 2);

      CAsset::drawRotBoxFill(frag, color, angle);
    }
  }

  CCanvas::stopDrawing();

  SDL_Rect srcR = CAsset::getRect(0,0,WWIDTH,WHEIGHT);
  SDL_Rect dstR = srcR;
  CSurface::OnDraw(transMask.canvas, dstR, srcR);
}

void CTransition::checkerin() {
  static const int max_W = 64;
  static const int cols = (WWIDTH / max_W)  + (bool)(max_W % WWIDTH);
  static const int rows = (WHEIGHT / max_W) + (bool)(max_W % WHEIGHT);
  static const int frag_wave_t = init_reset_time / 3; // time to initialize all fragments
  static const int frag_anim_t = init_reset_time - frag_wave_t; // time to complete a fragment animation
  static const int min_angle = -180;

  transMask.clearCanvas();
  transMask.beginDrawing();

  int t_elapsed = init_reset_time - fadein_timer;
  int Xo = -(max_W % WWIDTH)  / 2;
  int Yo = -(max_W % WHEIGHT) / 2;
  int col_init_dt = frag_wave_t / (cols - 1); // time between fragment inits for a column
  int row_init_dt = frag_wave_t / (rows - 1); // time between fragment inits for a row

  SDL_Rect frag;
  for (int i = 0; i < cols; i++) {
    for (int j = 0; j < rows; j++) {
      int col_end_t = (i * col_init_dt) + frag_anim_t; // t_elapsed when this column vanishes
      if (t_elapsed >= col_end_t) break;
      int row_end_t = (j * row_init_dt) + frag_anim_t; // t_elapsed when this row vanishes
      if (t_elapsed >= row_end_t) continue;

      int frag_t = (col_end_t < row_end_t) ? col_end_t - t_elapsed            : row_end_t - t_elapsed;
      int sz     = (frag_t < frag_anim_t)  ? max_W * frag_t / frag_anim_t     : max_W;
      int angle  = (frag_t < frag_anim_t)  ? min_angle * frag_t / frag_anim_t : min_angle;
      sz -= (sz % 2);
      frag.w = frag.h = sz;
      frag.x = Xo + (i * max_W) + ((max_W - sz) / 2);
      frag.y = Yo + (j * max_W) + ((max_W - sz) / 2);

      CAsset::drawRotBoxFill(frag, color, angle);
    }
  }

  CCanvas::stopDrawing();

  SDL_Rect srcR = CAsset::getRect(0,0,WWIDTH,WHEIGHT);
  SDL_Rect dstR = srcR;
  CSurface::OnDraw(transMask.canvas, dstR, srcR);
}
