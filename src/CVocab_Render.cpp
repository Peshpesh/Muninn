#include "CVocab.h"

void CVocab::OnRender(const SDL_Point& p) {
  using namespace vocab;

  CType::control.SetFont(FONT_DEFAULT);
  if (at_menu) {
    for (int i = 0; i <= GROUP_BY_ALPHA; i++) {
      CAsset::drawBoxFill(r_options[i], c_options);
      if (SDL_PointInRect(&p, &r_options[i])) {
        CAsset::paletteAlpha(MAX_RGBA / 5);
        CAsset::drawBoxFill(r_options[i], &palette::black);
        CAsset::paletteReset();
      }
      CType::CenterWrite(t_options[i], r_options[i], f_def);
    }    
  }
}
