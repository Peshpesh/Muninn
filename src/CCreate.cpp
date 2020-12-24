#include "CCreate.h"

CCreate CCreate::control;

CCreate::CCreate() {
  vocab_str = false;
  furi_str  = false;
  p_A.x = p_A.y = 0;
  p_B.x = p_B.y = 0;
}

bool CCreate::OnInit() {
  using namespace createcard;
  if (!vocabspace.initCanvas(vocab_line.w, vocab_line.h)) return false;
  if (!furispace.initCanvas(furi_line.w, furi_line.h)) return false;
  if (!compspace.initCanvas(comp_line.w, comp_line.h)) return false;
  return true;
}

void CCreate::OnEvent(SDL_Event* Event) {
  if (CTransition::control.isActive()) return;

  CEvent::OnEvent(Event);
}

void CCreate::OnLButtonDown(int mX, int mY) {
  using namespace createcard;
  const SDL_Point p = {mX, mY};

  if (SDL_PointInRect(&p, &vocab_line)) {
    vocab_str = true;
    p_A.x = p.x - vocab_line.x;
    p_A.y = p.y - vocab_line.y;
  } else if (SDL_PointInRect(&p, &furi_line)) {
    furi_str = true;
    p_A.x = p.x - furi_line.x;
    p_A.y = p.y - furi_line.y;
  }
}

void CCreate::OnLButtonUp(int mX, int mY) {
  vocab_str = furi_str = false;
}

void CCreate::OnLoop(const SDL_Point& p) {
  using namespace createcard;
  if (vocab_str || furi_str) {
    p_B.x = vocab_str ? p.x - vocab_line.x : p.x - furi_line.x;
    p_B.y = vocab_str ? p.y - vocab_line.y : p.y - furi_line.y;
    if (p_A.x != p_B.x || p_A.y != p_B.y) {
      short sz = vocab_str ? vocab_sz : furi_sz;
      short dx = p_B.x - p_A.x;
      short dy = p_B.y - p_A.y;
      double r = sqrt((dx * dx) + (dy * dy));
      double angle = atan2(dy,dx) * 180.0 / PI;

      SDL_Rect dstR;
      dstR.x = p_A.x;
      dstR.y = p_A.y - (sz / 2);
      dstR.w = r + sz;
      dstR.h = sz;

      SDL_Point anchor;
      anchor.x = 0;
      anchor.y = sz / 2;

      if (vocab_str) vocabspace.beginDrawing();
      else furispace.beginDrawing();

      CAsset::drawRotBoxFill(dstR, str_col, angle, &anchor);

      CCanvas::stopDrawing();

      p_A = p_B;
    }
  }
}

void CCreate::OnRender() {
  using namespace createcard;
  CAsset::drawBox(vocab_line, &palette::black);
  CAsset::drawBox(furi_line, &palette::silver);

  SDL_Rect srcR;
  srcR.x = srcR.y = 0;
  srcR.w = vocab_line.w;
  srcR.h = vocab_line.h;
  CSurface::OnDraw(vocabspace.canvas, srcR, vocab_line);

  srcR.w = furi_line.w;
  srcR.h = furi_line.h;
  CSurface::OnDraw(furispace.canvas, srcR, furi_line);
}
