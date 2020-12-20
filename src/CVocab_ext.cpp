#include "CVocab.h"

namespace vocab {
  const SDL_Color* f_def  = &rgb::black;
  const SDL_Color* bg_hue = &rgb::yellow;

  const short h_bfr = 64;
  const short w_bfr = 128;
  const short h_spac = 48;
  const short w_spac = 64;
  const short header_h = 128;
  const short w = (WWIDTH  - (w_bfr * 2) - (w_spac)) / 2;
  const short h = (WHEIGHT - (h_bfr * 2) - (h_spac * 2) - (header_h)) / 3;
  const short x = w_bfr;
  const short y = header_h + h_bfr;

  const SDL_Rect r_options[] = {
    CAsset::getRect(x,              y,                    w, h),
    CAsset::getRect(x + w + w_spac, y,                    w, h),
    CAsset::getRect(x,              y + h + h_spac,       w, h),
    CAsset::getRect(x + w + w_spac, y + h + h_spac,       w, h),
    CAsset::getRect(x,              y + (h + h_spac) * 2, w, h),
    CAsset::getRect(x + w + w_spac, y + (h + h_spac) * 2, w, h),
  };

  const char* const t_options[] = {
    "By Topic",
    "By Lesson",
    "By Familiarity",
    "By Frequency in Media",
    "By Difficulty",
    "From A to Z"
  };

  const SDL_Point* c_options = &palette::silver;
}
