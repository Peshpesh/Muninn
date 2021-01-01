#include "CTitle.h"

CTitle CTitle::control;

CTitle::CTitle() {
  call_terminate = false;
  transMode = NULL;
  listfont = LA_DEFAULT_SMOL;
}

bool CTitle::OnInit() {
  using namespace title;
  if (!TextLayer.initCanvas(r_opts[0].w, num_options * r_opts[0].h)) {
    return false;
  }

  TextLayer.beginDrawing();
  SDL_Texture* tmp_text = NULL;
  int line_h = CText::getLineH(listfont);
  SDL_Rect srcR, dstR;
  srcR.x = srcR.y = 0;

  for (int i = 0; i < num_options; i++) {
    if ((tmp_text = CText::drawText(listfont, t_opts[i], *f_def, &srcR)) == NULL) return false;
    dstR.x = (r_opts[0].w - srcR.w) / 2;
    dstR.y = (i * r_opts[0].h) + ((r_opts[0].h - line_h) / 2);
    dstR.w = srcR.w;
    dstR.h = srcR.h;
    CSurface::OnDraw(tmp_text, srcR, dstR);
  }

  // if ((tmp_text = CText::drawText(listfont, t_lesson, *f_def, &srcR)) == NULL) return false;
  // dstR.x = (optR.w - srcR.w) / 2;
  // dstR.y = (optR.h - line_h) / 2;
  // dstR.w = srcR.w;
  // dstR.h = srcR.h;
  // CSurface::OnDraw(tmp_text, srcR, dstR);

  // if ((tmp_text = CText::drawText(listfont, t_vocab, *f_def, &srcR)) == NULL) return false;
  // dstR.x = (optR.w - srcR.w) / 2;
  // dstR.y = optR.h + ((optR.h - line_h) / 2);
  // dstR.w = srcR.w;
  // dstR.h = srcR.h;
  // CSurface::OnDraw(tmp_text, srcR, dstR);

  // if ((tmp_text = CText::drawText(listfont, t_grammar, *f_def, &srcR)) == NULL) return false;
  // dstR.x = (optR.w - srcR.w) / 2;
  // dstR.y = 2 * optR.h + ((optR.h - line_h) / 2);
  // dstR.w = srcR.w;
  // dstR.h = srcR.h;
  // CSurface::OnDraw(tmp_text, srcR, dstR);

  SDL_DestroyTexture(tmp_text);
  TextLayer.stopDrawing();
  return true;
}

void CTitle::OnCleanup() {
  TextLayer.cleanup();
}
