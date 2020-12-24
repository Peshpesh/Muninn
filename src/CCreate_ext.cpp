#include "CCreate.h"

namespace createcard {
  const short vocab_sz = 5;
  const short furi_sz  = 3;
  const SDL_Point* str_col = &palette::black;
  const short line_x  = 64;
  const short line_y  = 96;
  const short line_w  = 1024;
  const short vocab_h = 192;
  const short furi_h  = 64;
  const SDL_Rect vocab_line = CAsset::getRect(line_x, line_y,           line_w, vocab_h);
  const SDL_Rect furi_line  = CAsset::getRect(line_x, line_y + vocab_h, line_w, furi_h);
  const SDL_Rect comp_line  = CAsset::getRect(line_x, line_y,           line_w, vocab_h + furi_h);
}
