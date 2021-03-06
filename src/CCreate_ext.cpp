#include "CCreate.h"

namespace createcard {
  const SDL_Color* bg_col = &rgb::charcoal;

  const SDL_Point* str_col = &palette::black;
  const short phrase_y = 96;
  const short phrase_w = 1080;
  const short phrase_h = 200;
  const short phrase_x = (WWIDTH - phrase_w) / 2;

  const short ent_spacing = 16;

  const short syllab_x = phrase_x;
  const short syllab_y = phrase_y + phrase_h + ent_spacing;
  const short syllab_w = phrase_w;
  const short syllab_h = 70;

  const short define_x = phrase_x;
  const short define_y = syllab_y + syllab_h + ent_spacing;
  const short define_w = phrase_w;
  const short define_h = 80;

  const SDL_Color* entry_col = &rgb::ash;
  const SDL_Rect phrase_entry = CAsset::getRect(phrase_x, phrase_y, phrase_w, phrase_h);
  const SDL_Rect syllab_entry = CAsset::getRect(syllab_x, syllab_y, syllab_w, syllab_h);
  const SDL_Rect define_entry = CAsset::getRect(define_x, define_y, define_w, define_h);

  const SDL_Color* txt_col  = &rgb::white;
  const SDL_Color* edit_col = &rgb::light_red;

  // const SDL_Rect romaji_entry  = CAsset::getRect(entry_x, entry_y,           entry_w, entry_h);
  // const SDL_Rect english_entry = CAsset::getRect(entry_x, entry_y + entry_h, entry_w, entry_h);

  const SDL_Rect save_button   = CAsset::getRect(0,0,0,0);
  const SDL_Rect clear_button  = CAsset::getRect(0,0,0,0);
}
