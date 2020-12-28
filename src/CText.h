#ifndef _C_TEXT_H_
#define _C_TEXT_H_

#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "CSurface.h"
#include "CError.h"

enum {

  JP_DEFAULT_HUGE = 0,
  JP_DEFAULT_LORGE,
  JP_DEFAULT_MID,
  JP_DEFAULT_SMOL,
  JP_DEFAULT_TINY,

  LA_DEFAULT_HUGE,
  LA_DEFAULT_LORGE,
  LA_DEFAULT_MID,
  LA_DEFAULT_SMOL,
  LA_DEFAULT_TINY

} fontID;

enum {
  HUGE_SIZE  = 160,
  LORGE_SIZE = 96,
  MID_SIZE   = 64,
  SMOL_SIZE  = 32,
  TINY_SIZE  = 12
} fontsize;

class CText {

  static std::vector<TTF_Font*> FontList;


public:

  static bool OnInit();

  static void OnCleanup();

  static TTF_Font* getFont(const short& ID);
  static SDL_Texture* drawText(const short& ID, char const* text, const SDL_Color& c, SDL_Rect* textureR);
  static int getLineH(const short& ID);
};

#endif
