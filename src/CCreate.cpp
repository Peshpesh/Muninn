#include "CCreate.h"

CCreate CCreate::control;

CCreate::CCreate() {
  testfont  = NULL;
  testfonttexture = NULL;
  vocab_str = false;
  furi_str  = false;
  p_A.x = p_A.y = 0;
  p_B.x = p_B.y = 0;
}

bool CCreate::OnInit() {
  using namespace createcard;
  if (!vocabspace.initCanvas(vocab_line.w, vocab_line.h)) return false;
  if (!furispace.initCanvas(furi_line.w, furi_line.h)) return false;
  if (!compspace.initCanvas(comp_line.w, comp_line.h)) return false;

  testfont = TTF_OpenFont("yumin.ttf", 96);
  if (testfont == NULL) return false;

  return true;
}

void CCreate::OnEvent(SDL_Event* Event) {
  if (CTransition::control.isActive()) return;

  CEvent::OnEvent(Event);
}

void CCreate::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
  switch (sym) {

  }
}

void CCreate::OnTextInput(char const* text) {

}

void CCreate::OnLButtonDown(int mX, int mY) {
  using namespace createcard;
  const SDL_Point p = {mX, mY};

  SDL_Color tmp_color = {0,0,0,255};
  // SDL_Surface* tmp_surf = TTF_RenderText_Solid(testfont, "aaaaa", tmp_color);
  Uint16 unicode_text[] = {12354, 12355,12356,26032,26033};
  SDL_Surface* tmp_surf = TTF_RenderUNICODE_Blended(testfont, unicode_text, tmp_color);
  if (tmp_surf != NULL) {
    SDL_Renderer* tmp_rend = CSurface::getRenderer();
    testfonttexture = SDL_CreateTextureFromSurface(tmp_rend, tmp_surf);
    SDL_FreeSurface(tmp_surf);
  }

  // std::string tmp  = "あああああ";
  // int tmpsz = tmp.size();
  //
  // FILE* FileHandle = fopen("binary.txt", "wb");
  // if (FileHandle == NULL) return;
  // fwrite(&tmpsz, sizeof(tmpsz), 1, FileHandle);
  // fwrite(tmp.c_str(), 1, tmpsz, FileHandle);
  // fclose(FileHandle);
  //
  // int tmpasz;
  // FileHandle = fopen("binary.txt", "rb");
  // if (FileHandle == NULL) return;
  // fread(&tmpasz, sizeof(tmpasz), 1, FileHandle);
  // std::string tmpa(tmpasz, 0);
  // fread(&tmpa[0], 1, tmpasz, FileHandle);
  // fclose(FileHandle);
  //
  // int tmpbsz = tmpa.size();
  // FileHandle = fopen("textmode.txt", "w");
  // if (FileHandle == NULL) return;
  // fprintf(FileHandle, "%d %d", tmpasz, tmpbsz);
  // fputs(tmpa.c_str(), FileHandle);
  // fclose(FileHandle);

  if (SDL_PointInRect(&p, &vocab_line)) {
    vocab_str = true;
    p_A.x = p.x - vocab_line.x;
    p_A.y = p.y - vocab_line.y;
  } else if (SDL_PointInRect(&p, &furi_line)) {
    furi_str = true;
    p_A.x = p.x - furi_line.x;
    p_A.y = p.y - furi_line.y;
  }
}

void CCreate::OnLButtonUp(int mX, int mY) {
  vocab_str = furi_str = false;
}

void CCreate::OnLoop(const SDL_Point& p) {
  using namespace createcard;
  if (vocab_str || furi_str) {
    p_B.x = vocab_str ? p.x - vocab_line.x : p.x - furi_line.x;
    p_B.y = vocab_str ? p.y - vocab_line.y : p.y - furi_line.y;
    if (p_A.x != p_B.x || p_A.y != p_B.y) {
      short sz = vocab_str ? vocab_sz : furi_sz;
      short dx = p_B.x - p_A.x;
      short dy = p_B.y - p_A.y;
      double r = sqrt((dx * dx) + (dy * dy));
      double angle = atan2(dy,dx) * 180.0 / PI;

      SDL_Rect dstR;
      dstR.x = p_A.x;
      dstR.y = p_A.y - (sz / 2);
      dstR.w = r + sz;
      dstR.h = sz;

      SDL_Point anchor;
      anchor.x = 0;
      anchor.y = sz / 2;

      if (vocab_str) vocabspace.beginDrawing();
      else furispace.beginDrawing();

      CAsset::drawRotBoxFill(dstR, str_col, angle, &anchor);

      CCanvas::stopDrawing();

      p_A = p_B;
    }
  }
}

void CCreate::OnRender() {
  using namespace createcard;

  CAsset::drawBoxFill(vocabtop, line_edge_col);
  CAsset::drawBoxFill(vocabbot, line_edge_col);
  CAsset::drawBoxFill(vocabmid, line_grid_col);

  // CAsset::drawBox(vocab_line, &palette::black, 3);
  // CAsset::drawBox(furi_line, &palette::silver, 3);

  SDL_Rect srcR;
  srcR.x = srcR.y = 0;
  srcR.w = vocab_line.w;
  srcR.h = vocab_line.h;
  CSurface::OnDraw(vocabspace.canvas, srcR, vocab_line);

  srcR.w = furi_line.w;
  srcR.h = furi_line.h;
  CAsset::drawBoxFill(furi_line, furi_line_col);
  CSurface::OnDraw(furispace.canvas, srcR, furi_line);

  if (testfonttexture != NULL) {
    SDL_Rect tmpR;
    tmpR.x = tmpR.y = 0;
    SDL_QueryTexture(testfonttexture, NULL, NULL, &tmpR.w, &tmpR.h);
    CSurface::OnDraw(testfonttexture, tmpR, tmpR);
  }
}
