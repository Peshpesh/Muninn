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
  const short edge_sz = 3;
  const short grid_sz = 1;
  const SDL_Rect vocab_line = CAsset::getRect(line_x, line_y,                     line_w, vocab_h);
  const SDL_Rect furi_line  = CAsset::getRect(line_x, line_y + vocab_h,           line_w, furi_h);
  const SDL_Rect comp_line  = CAsset::getRect(line_x, line_y,                     line_w, vocab_h + furi_h);
  const SDL_Rect vocabtop   = CAsset::getRect(line_x, line_y,                     line_w, edge_sz);
  const SDL_Rect vocabmid   = CAsset::getRect(line_x, line_y + (vocab_h / 2),     line_w, grid_sz);
  const SDL_Rect vocabbot   = CAsset::getRect(line_x, line_y + vocab_h - edge_sz, line_w, edge_sz);
  const SDL_Point* line_edge_col = &palette::gray;
  const SDL_Point* line_grid_col = &palette::silver;
  const SDL_Color furi_line_col  = {MAX_RGBA, MAX_RGBA, 186}; // manilla

  const short entry_x = line_x;
  const short entry_y = 400;
  const short entry_w = line_w;
  const short entry_h = 64;
  const SDL_Rect romaji_entry  = CAsset::getRect(entry_x, entry_y,           entry_w, entry_h);
  const SDL_Rect english_entry = CAsset::getRect(entry_x, entry_y + entry_h, entry_w, entry_h);

  const SDL_Rect save_button   = CAsset::getRect(0,0,0,0);
  const SDL_Rect clear_button  = CAsset::getRect(0,0,0,0);
}
