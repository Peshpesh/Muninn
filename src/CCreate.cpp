#include "CCreate.h"

CCreate CCreate::control;

CCreate::CCreate() {
  bigfont = NULL;
  smolfont = NULL;

  candidatetexture = NULL;
  write_target = 0;

  phraseR.x = createcard::phrase_entry.x;
  phraseR.y = createcard::phrase_entry.y;
  phraseR.w = phraseR.h = 0;

  syllabaryR.x = createcard::syllab_entry.x;
  syllabaryR.y = createcard::syllab_entry.y;
  syllabaryR.w = syllabaryR.h = 0;

  candidateR.x = candidateR.y = candidateR.w = candidateR.h = 0;

  defineR.x = createcard::define_entry.x;
  defineR.y = createcard::define_entry.y;
  defineR.w = defineR.h = 0;
}

bool CCreate::OnInit() {
  using namespace createcard;

  if (!phrasecanvas.initCanvas(phrase_entry.w, phrase_entry.h)) return false;
  if (!syllabarycanvas.initCanvas(syllab_entry.w, syllab_entry.h)) return false;
  if (!definecanvas.initCanvas(define_entry.w, define_entry.h)) return false;

  // font = TTF_OpenFont("yumin.ttf", 64);
  bigfont = TTF_OpenFont("msgothic.ttc", 96);
  if (bigfont == NULL) return false;
  smolfont = TTF_OpenFont("msgothic.ttc", 32);
  if (smolfont == NULL) return false;

  phrasetext.push_back("");
  syllabarytext.push_back("");
  definetext.push_back("");

  return true;
}

void CCreate::OnEvent(SDL_Event* Event) {
  if (CTransition::control.isActive()) return;

  CEvent::OnEvent(Event);
}

void CCreate::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
  switch (sym) {
    default: break;
  }
}

void CCreate::OnTextInput(char const* text) {
  SDL_Color tmp_color = {0,0,0,255};
  SDL_Surface* tmp_surf = NULL;

  switch (write_target) {
    case createcard::W_PHRASE: {
      {
        // check if the last line is getting too long
        int line = phrasetext.size() - 1;
        std::string tmpstr = phrasetext[line] + text;
        int w = 0;
        TTF_SizeUTF8(bigfont, tmpstr.c_str(), &w, NULL);
        if (w > createcard::phrase_entry.w) {
          // last line is too long; start a new one
          phrasetext.push_back(text);
        } else {
          // last line is not too long; append text to it
          phrasetext[line] += text;
        }
      }

      phrasecanvas.clearCanvas();
      int line_h = TTF_FontLineSkip(bigfont);
      for (int i = 0; i < phrasetext.size(); i++) {
        tmp_surf = TTF_RenderUTF8_Blended(bigfont, phrasetext[i].c_str(), tmp_color);
        if (tmp_surf) {
          SDL_Texture* tmp_text = SDL_CreateTextureFromSurface(CSurface::getRenderer(), tmp_surf);
          SDL_FreeSurface(tmp_surf);
          if (tmp_text) {
            SDL_QueryTexture(tmp_text, NULL, NULL, &phraseR.w, &phraseR.h);
            phrasecanvas.beginDrawing();
            SDL_Rect srcR = phraseR;
            srcR.x = srcR.y = 0;
            SDL_Rect dstR = srcR;
            dstR.y = i * line_h;
            CSurface::OnDraw(tmp_text, srcR, dstR);
            phrasecanvas.stopDrawing();
            SDL_DestroyTexture(tmp_text);
          }
        }
      }
      break;
    }
    case createcard::W_SYLLAB: {
      {
        // check if the last line is getting too long
        int line = syllabarytext.size() - 1;
        std::string tmpstr = syllabarytext[line] + text;
        int w = 0;
        TTF_SizeUTF8(smolfont, tmpstr.c_str(), &w, NULL);
        if (w > createcard::syllab_entry.w) {
          // last line is too long; start a new one
          syllabarytext.push_back(text);
        } else {
          // last line is not too long; append text to it
          syllabarytext[line] += text;
        }
      }

      syllabarycanvas.clearCanvas();
      int line_h = TTF_FontLineSkip(smolfont);
      for (int i = 0; i < syllabarytext.size(); i++) {
        tmp_surf = TTF_RenderUTF8_Blended(smolfont, syllabarytext[i].c_str(), tmp_color);
        if (tmp_surf) {
          SDL_Texture* tmp_text = SDL_CreateTextureFromSurface(CSurface::getRenderer(), tmp_surf);
          SDL_FreeSurface(tmp_surf);
          if (tmp_text) {
            SDL_QueryTexture(tmp_text, NULL, NULL, &syllabaryR.w, &syllabaryR.h);
            syllabarycanvas.beginDrawing();
            SDL_Rect srcR = syllabaryR;
            srcR.x = srcR.y = 0;
            SDL_Rect dstR = srcR;
            dstR.y = i * line_h;
            CSurface::OnDraw(tmp_text, srcR, dstR);
            syllabarycanvas.stopDrawing();
            SDL_DestroyTexture(tmp_text);
          }
        }
      }
      break;
    }
    case createcard::W_DEFINE: {
      {
        // check if the last line is getting too long
        int line = definetext.size() - 1;
        std::string tmpstr = definetext[line] + text;
        int w = 0;
        TTF_SizeUTF8(smolfont, tmpstr.c_str(), &w, NULL);
        if (w > createcard::define_entry.w) {
          // last line is too long; start a new one
          definetext.push_back(text);
        } else {
          // last line is not too long; append text to it
          definetext[line] += text;
        }
      }

      definecanvas.clearCanvas();
      int line_h = TTF_FontLineSkip(smolfont);
      for (int i = 0; i < definetext.size(); i++) {
        tmp_surf = TTF_RenderUTF8_Blended(smolfont, definetext[i].c_str(), tmp_color);
        if (tmp_surf) {
          SDL_Texture* tmp_text = SDL_CreateTextureFromSurface(CSurface::getRenderer(), tmp_surf);
          SDL_FreeSurface(tmp_surf);
          if (tmp_text) {
            SDL_QueryTexture(tmp_text, NULL, NULL, &defineR.w, &defineR.h);
            definecanvas.beginDrawing();
            SDL_Rect srcR = defineR;
            srcR.x = srcR.y = 0;
            SDL_Rect dstR = srcR;
            dstR.y = i * line_h;
            CSurface::OnDraw(tmp_text, srcR, dstR);
            definecanvas.stopDrawing();
            SDL_DestroyTexture(tmp_text);
          }
        }
      }
      break;
    }
  }
}

void CCreate::OnTextEditing(char const* text, Sint32 start, Sint32 length) {
  if (candidatetexture) SDL_DestroyTexture(candidatetexture);

  if (text[0] == '\0') return;

  SDL_Color tmp_color = {255,0,0,255};
  SDL_Surface* tmp_surf = TTF_RenderUTF8_Blended((write_target == createcard::W_PHRASE) ? bigfont : smolfont, text, tmp_color);
  if (tmp_surf != NULL) {
    candidatetexture = SDL_CreateTextureFromSurface(CSurface::getRenderer(), tmp_surf);
    SDL_FreeSurface(tmp_surf);
    if (candidatetexture != NULL) {
      SDL_QueryTexture(candidatetexture, NULL, NULL, &candidateR.w, &candidateR.h);
      switch (write_target) {
        case createcard::W_PHRASE: {
          // check if the last line is getting too long
          int line = phrasetext.size() - 1;
          std::string tmpstr = phrasetext[line] + text;
          int w = 0;
          TTF_SizeUTF8(bigfont, tmpstr.c_str(), &w, NULL);
          int line_h = TTF_FontLineSkip(bigfont);
          if (w > createcard::phrase_entry.w) {
            candidateR.x = phraseR.x;
            candidateR.y = phraseR.y + line_h * phrasetext.size();
          } else {
            candidateR.x = phraseR.x + phraseR.w;
            candidateR.y = phraseR.y + line_h * (phrasetext.size() - 1);
          }
          break;
        }
        case createcard::W_SYLLAB: {
          // check if the last line is getting too long
          int line = syllabarytext.size() - 1;
          std::string tmpstr = syllabarytext[line] + text;
          int w = 0;
          TTF_SizeUTF8(smolfont, tmpstr.c_str(), &w, NULL);
          int line_h = TTF_FontLineSkip(smolfont);
          if (w > createcard::syllab_entry.w) {
            candidateR.x = syllabaryR.x;
            candidateR.y = syllabaryR.y + line_h * syllabarytext.size();
          } else {
            candidateR.x = syllabaryR.x + syllabaryR.w;
            candidateR.y = syllabaryR.y + line_h * (syllabarytext.size() - 1);
          }
          break;
        }
        case createcard::W_DEFINE: {
          // check if the last line is getting too long
          int line = definetext.size() - 1;
          std::string tmpstr = definetext[line] + text;
          int w = 0;
          TTF_SizeUTF8(smolfont, tmpstr.c_str(), &w, NULL);
          int line_h = TTF_FontLineSkip(smolfont);
          if (w > createcard::define_entry.w) {
            candidateR.x = defineR.x;
            candidateR.y = defineR.y + line_h * definetext.size();
          } else {
            candidateR.x = defineR.x + defineR.w;
            candidateR.y = defineR.y + line_h * (definetext.size() - 1);
          }
          break;
        }
      }
    }
  }
}

void CCreate::OnLButtonDown(int mX, int mY) {
  using namespace createcard;
  const SDL_Point p = {mX, mY};

  char orig_target = write_target;

  if (SDL_PointInRect(&p, &phrase_entry)) {
    write_target = W_PHRASE;
  } else if (SDL_PointInRect(&p, &syllab_entry)) {
    write_target = W_SYLLAB;
  } else if (SDL_PointInRect(&p, &define_entry)) {
    write_target = W_DEFINE;
  } else {
    write_target = 0;
  }

  if (write_target != orig_target) {
    if (SDL_IsTextInputActive()) SDL_StopTextInput();
    if (write_target) {
      switch (write_target) {
        case W_PHRASE: {
          SDL_SetTextInputRect(&phraseR);
          break;
        }
        case W_SYLLAB: {
          SDL_SetTextInputRect(&syllabaryR);
          break;
        }
        case W_DEFINE: {
          SDL_SetTextInputRect(&defineR);
          break;
        }
      }
      SDL_StartTextInput();
    }
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

  // if (SDL_PointInRect(&p, &vocab_line)) {
  //   vocab_str = true;
  //   p_A.x = p.x - vocab_line.x;
  //   p_A.y = p.y - vocab_line.y;
  // } else if (SDL_PointInRect(&p, &furi_line)) {
  //   furi_str = true;
  //   p_A.x = p.x - furi_line.x;
  //   p_A.y = p.y - furi_line.y;
  // }
}

void CCreate::OnLButtonUp(int mX, int mY) {

}

void CCreate::OnLoop(const SDL_Point& p) {

}

void CCreate::OnRender() {
  using namespace createcard;

  CAsset::drawBoxFill(phrase_entry, &palette::yellow);
  CAsset::drawBoxFill(syllab_entry, &palette::green);
  CAsset::drawBoxFill(define_entry, &palette::cyan);

  CSurface::OnDraw(phrasecanvas.canvas, phrasecanvas.canvR, phrase_entry);
  CSurface::OnDraw(syllabarycanvas.canvas, syllabarycanvas.canvR, syllab_entry);
  CSurface::OnDraw(definecanvas.canvas, definecanvas.canvR, define_entry);

  if (candidatetexture != NULL) {
    SDL_Rect srcR = candidateR;
    srcR.x = srcR.y = 0;
    CSurface::OnDraw(candidatetexture, srcR, candidateR);
  }
}
