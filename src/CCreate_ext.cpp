#include "CCreate.h"

namespace createcard {
  const SDL_Point* str_col = &palette::black;
  const short phrase_x = 64;
  const short phrase_y = 96;
  const short phrase_w = 1024;
  const short phrase_h = 192;

  const short entry_x = phrase_x;
  const short entry_y = 400;
  const short entry_w = phrase_w;
  const short entry_h = 64;

  const SDL_Rect phrase_entry = CAsset::getRect(phrase_x, phrase_y,            phrase_w, phrase_h);
  const SDL_Rect syllab_entry = CAsset::getRect(phrase_x, phrase_y + phrase_h, phrase_w, entry_h);
  const SDL_Rect define_entry = CAsset::getRect(entry_x, entry_y, entry_w, entry_h);

  const SDL_Rect romaji_entry  = CAsset::getRect(entry_x, entry_y,           entry_w, entry_h);
  const SDL_Rect english_entry = CAsset::getRect(entry_x, entry_y + entry_h, entry_w, entry_h);

  const SDL_Rect save_button   = CAsset::getRect(0,0,0,0);
  const SDL_Rect clear_button  = CAsset::getRect(0,0,0,0);
}
