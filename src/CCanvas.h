#ifndef _C_CANVAS_H_
#define _C_CANVAS_H_

#include "CSurface.h"

class CCanvas {

public:
  SDL_Texture* canvas;    // the working canvas upon which to apply a mask
  SDL_Rect canvR;

public:
  CCanvas();

  bool initCanvas(const int& W, const int& H);

  /* clear the canvas */
  void clearCanvas();

  /* set the canvas as the rendering target */
  void beginDrawing();

  /* disable the canvas as a rendering target */
  void stopDrawing();

  /* enable rendering to the canvas, draw onto it, and then disable rendering */
  void drawToCanvas(SDL_Texture* src_img, const SDL_Rect& srcR, const int& X, const int& Y);
  void drawToCanvas(SDL_Texture* src_img, const SDL_Rect& srcR, const SDL_Point& dstP);
  void drawToCanvas(SDL_Texture* src_img, const SDL_Rect& srcR, const SDL_Rect& dstR);

  void cleanup();

};
#endif
