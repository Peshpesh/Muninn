#include "CTitle.h"

namespace title {
  const SDL_Color* bg_col = &rgb::charcoal;
  const SDL_Color* f_def = &rgb::black;
  const SDL_Color* f_hov = &rgb::black;
  const SDL_Color* f_lock = &rgb::white;
  // const SDL_Point* o_def = &palette::white;
  // const SDL_Point* o_hov = &palette::light_green;
  // const SDL_Point* o_lock = &palette::gray;
  // const short num_options = 4;
  // const char* const opt_list[] = {
  //   "New", "Load", "Options", "Quit",
  // }

  const short bfr = 64;  // distance between "business" and the window border
  const short spac = 16; // distance between selection buttons
  const short header_h = 128; // height of header/title space
  const short w = (WWIDTH  - (bfr * 2) - (spac * 2)) / 3;
  const short h = (WHEIGHT - (bfr * 2) - (spac * 5) - (header_h)) / 6;
  const short x = (WWIDTH - w) / 2;
  const short y = header_h + bfr;

  const SDL_Rect r_opts[] = {
    CAsset::getRect(x, y, w, h),
    CAsset::getRect(x, y + (spac + h), w, h),
    CAsset::getRect(x, y + (spac + h) * 2, w, h),
    CAsset::getRect(x, y + (spac + h) * 3, w, h),
    CAsset::getRect(x, y + (spac + h) * 4, w, h),
    CAsset::getRect(x, y + (spac + h) * 5, w, h)
  };

  const char* const t_opts[] = {
    "Lessons",
    "Vocabulary",
    "Grammar",
    "Practice",
    "Add Material",
    "Your Progress"
  };

  const SDL_Point* c_opts[] = {
    &palette::green,
    &palette::yellow,
    &palette::magenta,
    &palette::blue,
    &palette::cyan,
    &palette::violet
  };

  const app_module a_opts[] = {
    APP_MODE_LESSON,
    APP_MODE_VOCAB,
    APP_MODE_GRAMMAR,
    APP_MODE_PRACTICE,
    APP_MODE_NEW,
    APP_MODE_STATS,
  };

  const short num_options = 6;

  // const SDL_Rect r_lesson   = CAsset::getRect(x, y, w, h);
  // const SDL_Rect r_vocab    = CAsset::getRect(x, y + (spac + h), w, h);
  // const SDL_Rect r_grammar  = CAsset::getRect(x, y + (spac + h) * 2, w, h);
  // const SDL_Rect r_practice = CAsset::getRect(x, y + (spac + h) * 3, w, h);
  // const SDL_Rect r_add      = CAsset::getRect(x, y + (spac + h) * 4, w, h);
  // const SDL_Rect r_stats    = CAsset::getRect(x, y + (spac + h) * 5, w, h);
  //
  // const char* const t_lesson    = "Lessons";
  // const char* const t_vocab     = "Vocabulary";
  // const char* const t_grammar   = "Grammar";
  // const char* const t_practice  = "Practice";
  // const char* const t_add       = "Add Material";
  // const char* const t_stats     = "Your Progress";
  //
  // const SDL_Point* c_lesson   = &palette::green;
  // const SDL_Point* c_vocab    = &palette::yellow;
  // const SDL_Point* c_grammar  = &palette::magenta;
  // const SDL_Point* c_practice = &palette::blue;
  // const SDL_Point* c_add      = &palette::cyan;
  // const SDL_Point* c_stats    = &palette::violet;
}
