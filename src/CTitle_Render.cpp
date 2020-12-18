#include "CTitle.h"

bool CTitle::OnRender(const SDL_Point& p) {
  using namespace title;

  static const SDL_Rect* opts[] = {
    &r_lesson,
    &r_vocab,
    &r_grammar,
    &r_practice,
    &r_add,
    &r_stats
  };

  bool retval = false;
  CType::control.SetFont(FONT_DEFAULT);

  CAsset::drawBoxFill(r_lesson,   c_lesson);
  CAsset::drawBoxFill(r_vocab,    c_vocab);
  CAsset::drawBoxFill(r_grammar,  c_grammar);
  CAsset::drawBoxFill(r_practice, c_practice);
  CAsset::drawBoxFill(r_add,      c_add);
  CAsset::drawBoxFill(r_stats,    c_stats);

  for (int i = 0; i < sizeof(opts)/sizeof(opts[0]); i++) {
    if (SDL_PointInRect(&p, opts[i])) {
      CAsset::paletteAlpha(MAX_RGBA / 5);
      CAsset::drawBoxFill(*opts[i], &palette::black);
      CAsset::paletteReset();
    }
  }

  CType::CenterWrite(t_lesson,   r_lesson,   f_def);
  CType::CenterWrite(t_vocab,    r_vocab,    f_def);
  CType::CenterWrite(t_grammar,  r_grammar,  f_def);
  CType::CenterWrite(t_practice, r_practice, f_def);
  CType::CenterWrite(t_add,      r_add,      f_def);
  CType::CenterWrite(t_stats,    r_stats,    f_def);

  // switch (menu_kind) {
  //   case Title::MAIN:       retval = drawMainMenu(); break;
  //   case Title::NEW_GAME:   retval = drawNewGame();  break;
  //   case Title::LOAD_GAME:  retval = drawLoadGame(); break;
  //   case Title::OPTIONS:    retval = drawOptions();  break;
  //   default: break;
  // }

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
  return retval;
}
