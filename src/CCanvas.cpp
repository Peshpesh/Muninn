#include "CCanvas.h"

CCanvas::CCanvas() {
  canvas   = NULL;
  canvR.x  = canvR.y = canvR.w = canvR.h = 0;
}

/*
 * Create a new canvas texture with width W and height H.
 * If a texture already exists, then replace it.
 */
bool CCanvas::initCanvas(const int& W, const int& H) {
  if (canvas) SDL_DestroyTexture(canvas);
  if ((canvas = CSurface::CreateTargetTexture(W, H)) == NULL) return false;
  SDL_SetTextureBlendMode(canvas, SDL_BLENDMODE_BLEND);

  canvR.w = W;
  canvR.h = H;
  clearCanvas();

  return true;
}

void CCanvas::clearCanvas() {
  if (canvas == NULL) return;
  CSurface::ClearTargetTexture(canvas);
}

void CCanvas::beginDrawing() {
  if (canvas == NULL) return;
  CSurface::SetTargetTexture(canvas, false);
}

void CCanvas::stopDrawing() {
  CSurface::FreeTargetTexture();
}

void CCanvas::drawToCanvas(SDL_Texture* src_img, const SDL_Rect& srcR, const int& X, const int& Y) {
  if (src_img == NULL || canvas == NULL) return;

  CSurface::SetTargetTexture(canvas, false);

  SDL_Point dstP;
  dstP.x = X;
  dstP.y = Y;

  CSurface::OnDraw(src_img, srcR, dstP);

  CSurface::FreeTargetTexture();
}

void CCanvas::drawToCanvas(SDL_Texture* src_img, const SDL_Rect& srcR, const SDL_Point& dstP) {
  if (src_img == NULL || canvas == NULL) return;

  CSurface::SetTargetTexture(canvas, false);

  CSurface::OnDraw(src_img, srcR, dstP);

  CSurface::FreeTargetTexture();
}

void CCanvas::drawToCanvas(SDL_Texture* src_img, const SDL_Rect& srcR, const SDL_Rect& dstR) {
  if (src_img == NULL || canvas == NULL) return;

  CSurface::SetTargetTexture(canvas, false);

  CSurface::OnDraw(src_img, srcR, dstR);

  CSurface::FreeTargetTexture();
}

// void CCanvas::render(const int& X, const int& Y) {
//   if (canvas == NULL) return;
//   CSurface::OnDraw(canvas, X, Y);
// }

void CCanvas::cleanup() {
  SDL_DestroyTexture(canvas);
}
