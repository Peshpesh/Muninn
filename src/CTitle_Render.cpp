#include "CTitle.h"

void CTitle::OnRender(const SDL_Point& p) {
  using namespace title;

  // bool retval = false;

  CAsset::fillScreen(*bg_col);

  SDL_Rect fsrcR;
  fsrcR.x = 0;
  fsrcR.w = r_opts[0].w;
  fsrcR.h = r_opts[0].h;
  for (int i = 0; i < num_options; i++) {
    fsrcR.y = i * r_opts[0].h;
    CAsset::drawBoxFill(r_opts[i], c_opts[i]);
    CSurface::OnDraw(TextLayer.canvas, fsrcR, r_opts[i]);
    if (SDL_PointInRect(&p, &r_opts[i])) {
      CAsset::paletteAlpha(MAX_RGBA / 5);
      CAsset::drawBoxFill(r_opts[i], &palette::black);
      CAsset::paletteReset();
    }
  }

  // SDL_Rect srcR, dstR;
  // srcR.x = srcR.y = 0;
  // srcR.w = r_opts[0].w;
  // srcR.h = r_opts[0].h * num_options;
  // dstR = srcR;
  //
  // CSurface::OnDraw(TextLayer.canvas, srcR, dstR);

  // CMask test;
  // int W = 0;
  // CType::getLineDims(FONT_DEFAULT, t_lesson, W);
  // int H = CType::GetSymH(FONT_DEFAULT);
  //
  // SDL_Texture* new_mask = CSurface::CreateTargetTexture(W, H);
  // CSurface::SetTargetTexture(new_mask, true);
  // static SDL_Point origin = {0,0};
  // static SDL_Point pos = {0,0};
  // static bool osc = true;
  // static const int xmax = 4;
  // static const int ymax = 4;
  // CType::Write(FONT_DEFAULT, t_lesson, origin, f_def);
  // CSurface::FreeTargetTexture();
  //
  // if (osc) {
  //   pos.x++;
  //   pos.y++;
  // } else {
  //   pos.x--;
  //   pos.y--;
  // }
  //
  // if (pos.x == 0 || pos.x == xmax) {
  //   osc = !(osc);
  // }
  //
  // test.setMask(new_mask);
  // test.beginDrawing();
  // CType::Write(FONT_DEFAULT, t_lesson, pos, &rgb::red);
  // test.stopDrawing();
  // test.makeCompound();
  // return retval;
}
