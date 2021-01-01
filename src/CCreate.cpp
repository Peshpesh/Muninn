#include "CCreate.h"

CCreate CCreate::control;

CCreate::CCreate() {
  write_target = 0;
  update_target = false;

  phrasefont = JP_DEFAULT_LORGE;
  syllabaryfont = JP_DEFAULT_MID;
  definefont = LA_DEFAULT_SMOL;

  candidateR.x = candidateR.y = candidateR.w = candidateR.h = 0;

  info_alpha = 0.33 * MAX_RGBA;
}

bool CCreate::OnInit() {
  using namespace createcard;

  if (!phrasecanvas.initCanvas(phrase_entry.w, phrase_entry.h)) return false;
  if (!syllabarycanvas.initCanvas(syllab_entry.w, syllab_entry.h)) return false;
  if (!definecanvas.initCanvas(define_entry.w, define_entry.h)) return false;
  if (!infocanvas.initCanvas(phrase_entry.w, phrase_entry.h + syllab_entry.h + define_entry.h)) return false;

  phrasetext.push_back("");
  syllabarytext.push_back("");
  definetext.push_back("");

  SDL_Rect dstR, srcR;
  srcR.x = srcR.y = 0;

  SDL_Texture* tmp_text;
  int line_h;

  infocanvas.beginDrawing();

  if ((tmp_text = CText::drawItalicText(LA_DEFAULT_LORGE, "Word or phrase", *txt_col, &srcR)) == NULL) return false;
  line_h = CText::getLineH(LA_DEFAULT_LORGE);
  dstR = srcR;
  dstR.x = (phrase_entry.w - srcR.w) / 2;
  dstR.y = (phrase_entry.h - line_h) / 2;
  CSurface::OnDraw(tmp_text, srcR, dstR);
  SDL_DestroyTexture(tmp_text);

  if ((tmp_text = CText::drawItalicText(LA_DEFAULT_SMOL, "Kana (optional)", *txt_col, &srcR)) == NULL) return false;
  line_h = CText::getLineH(LA_DEFAULT_SMOL);
  dstR = srcR;
  dstR.x = (syllab_entry.w - srcR.w) / 2;
  dstR.y = phrase_entry.h + ((syllab_entry.h - line_h) / 2);
  CSurface::OnDraw(tmp_text, srcR, dstR);
  SDL_DestroyTexture(tmp_text);

  if ((tmp_text = CText::drawItalicText(definefont, "Translation", *txt_col, &srcR)) == NULL) return false;
  line_h = CText::getLineH(definefont);
  dstR = srcR;
  dstR.x = (define_entry.w - srcR.w) / 2;
  dstR.y = phrase_entry.h + syllab_entry.h + ((define_entry.h - line_h) / 2);
  CSurface::OnDraw(tmp_text, srcR, dstR);
  SDL_DestroyTexture(tmp_text);

  infocanvas.stopDrawing();

  SDL_SetTextureAlphaMod(infocanvas.canvas, info_alpha);

  return true;
}

void CCreate::OnEvent(SDL_Event* Event) {
  if (CTransition::control.isActive()) return;

  CEvent::OnEvent(Event);
}

void CCreate::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
  switch (sym) {
    case SDLK_BACKSPACE: {
      if (candidatetext.empty()) {
        // note: I still don't really get how the binary stuff works
        std::vector<std::string> *strptr = NULL;
        switch (write_target) {
          case createcard::W_PHRASE: strptr = &phrasetext; break;
          case createcard::W_SYLLAB: strptr = &syllabarytext; break;
          case createcard::W_DEFINE: strptr = &definetext; break;
        }

        if (strptr != NULL) {
          int idx = (*strptr).size() - 1;  // index of last string in vector
          int textlen = (*strptr)[idx].size();  // length of last string
          while (true) {
            if (textlen == 0) break;
            if (((*strptr)[idx][textlen-1] & 0x80) == 0x00)
            {
              /* One byte */
              (*strptr)[idx].erase((*strptr)[idx].end()-1);
              break;
            }
            if (((*strptr)[idx][textlen-1] & 0xC0) == 0x80)
            {
              /* Byte from the multibyte sequence */
              (*strptr)[idx].erase((*strptr)[idx].end()-1);
              textlen--;
            }
            if (((*strptr)[idx][textlen-1] & 0xC0) == 0xC0)
            {
              /* First byte of multibyte sequence */
              (*strptr)[idx].erase((*strptr)[idx].end()-1);
              break;
            }
          }
          // remove the string from the vector if it's now empty and not the only string
          if (idx != 0 && (*strptr)[idx].empty()) {
            (*strptr).erase((*strptr).end()-1);
          }
        }
      }
      break;
    }
    default: break;
  }
}

void CCreate::OnTextInput(char const* text) {
  using namespace createcard;

  update_target = true;

  switch (write_target) {
    case W_PHRASE: {
      // check if the last line is getting too long
      int line = phrasetext.size() - 1;
      std::string tmpstr = phrasetext[line] + text;
      int w = 0;
      TTF_SizeUTF8(CText::getFont(phrasefont), tmpstr.c_str(), &w, NULL);
      if (w > phrase_entry.w) {
        // last line is too long; start a new one
        phrasetext.push_back(text);
      } else {
        // last line is not too long; append text to it
        phrasetext[line] += text;
      }
      break;
    }
    case W_SYLLAB: {
      // check if the last line is getting too long
      int line = syllabarytext.size() - 1;
      std::string tmpstr = syllabarytext[line] + text;
      int w = 0;
      TTF_SizeUTF8(CText::getFont(syllabaryfont), tmpstr.c_str(), &w, NULL);
      if (w > syllab_entry.w) {
        // last line is too long; start a new one
        syllabarytext.push_back(text);
      } else {
        // last line is not too long; append text to it
        syllabarytext[line] += text;
      }
      break;
    }
    case W_DEFINE: {
      // check if the last line is getting too long
      int line = definetext.size() - 1;
      std::string tmpstr = definetext[line] + text;
      int w = 0;
      TTF_SizeUTF8(CText::getFont(definefont), tmpstr.c_str(), &w, NULL);
      if (w > define_entry.w) {
        // last line is too long; start a new one
        definetext.push_back(text);
      } else {
        // last line is not too long; append text to it
        definetext[line] += text;
      }
      break;
    }
  }
}

void CCreate::OnTextEditing(char const* text, Sint32 start, Sint32 length) {
  using namespace createcard;
  update_target = true;
  candidatetext = text;
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
    candidatetext.clear();
    switch (orig_target) {
      case W_PHRASE: updateEntry(&phrasetext, phrasefont, phrasecanvas, phrase_entry); break;
      case W_SYLLAB: updateEntry(&syllabarytext, syllabaryfont, syllabarycanvas, syllab_entry); break;
      case W_DEFINE: updateEntry(&definetext, definefont, definecanvas, define_entry); break;
    }
    if (write_target) {
      switch (write_target) {
        case W_PHRASE: {
          // SDL_SetTextInputRect(&phraseR);
          break;
        }
        case W_SYLLAB: {
          // SDL_SetTextInputRect(&syllabaryR);
          break;
        }
        case W_DEFINE: {
          // SDL_SetTextInputRect(&defineR);
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

void CCreate::OnLoop() {
  if (!update_target) return;
  using namespace createcard;

  switch (write_target) {
    case W_PHRASE: updateEntry(&phrasetext, phrasefont, phrasecanvas, phrase_entry); break;
    case W_SYLLAB: updateEntry(&syllabarytext, syllabaryfont, syllabarycanvas, syllab_entry); break;
    case W_DEFINE: updateEntry(&definetext, definefont, definecanvas, define_entry); break;
  }
}

void CCreate::updateEntry(std::vector<std::string> *text, const short& fontID, CCanvas& canvobj, const SDL_Rect& entryR) {
  if (text == NULL) return;

  int extended_last_w = 0; // width of last line extended with candidate text
  bool cand_newline = false;

  if (!candidatetext.empty()) {
    // check if the last line is too long with the candidate added
    int line = (*text).size() - 1;
    std::string tmpstr = (*text)[line] + candidatetext;
    TTF_SizeUTF8(CText::getFont(fontID), tmpstr.c_str(), &extended_last_w, NULL);
    if (extended_last_w > entryR.w) {
      // last line is too long with candidate added
      cand_newline = true;
    }
  }

  canvobj.clearCanvas();

  int line_h  = CText::getLineH(fontID);
  int total_h = line_h * ((*text).size() + (bool)(cand_newline));
  SDL_Rect dstR, srcR;
  srcR.x = srcR.y = 0;
  for (int i = 0; i < (*text).size(); i++) {
    SDL_Texture* tmp_text = CText::drawText(fontID, (*text)[i].c_str(), *createcard::txt_col, &srcR);
    if (tmp_text) {
      canvobj.beginDrawing();

      dstR = srcR;
      if (i == (*text).size() - 1 && !candidatetext.empty() && !cand_newline) {
        dstR.x = (entryR.w - extended_last_w) / 2; // extended centered line
      } else {
        dstR.x = (entryR.w - dstR.w) / 2; // regular centered line
      }
      dstR.y = ((entryR.h - total_h) / 2) + (i * line_h);
      CSurface::OnDraw(tmp_text, srcR, dstR);

      canvobj.stopDrawing();
      SDL_DestroyTexture(tmp_text);
    }
  }

  if (!candidatetext.empty()) {
    SDL_Texture* tmp_text = CText::drawText(fontID, candidatetext.c_str(), *createcard::edit_col, &srcR);
    if (tmp_text) {
      canvobj.beginDrawing();

      /* Note here that dstR represents the dims of the
         last rendered line (without the candidate) on canvas */
      candidateR = srcR;
      if (cand_newline) {
        candidateR.x = (entryR.w - candidateR.w) / 2; // new centered line
        candidateR.y = dstR.y + line_h;
      } else if (!(*text)[0].empty()) {
        candidateR.x = dstR.x + dstR.w; // extended centered line
        candidateR.y = dstR.y;
      } else {
        candidateR.x = (entryR.w - candidateR.w) / 2; // new centered line
        candidateR.y = (entryR.h - candidateR.h) / 2;
      }

      CSurface::OnDraw(tmp_text, srcR, candidateR);

      canvobj.stopDrawing();
      SDL_DestroyTexture(tmp_text);
    }
  }
}

void CCreate::OnRender() {
  using namespace createcard;

  CAsset::fillScreen(*bg_col);

  CAsset::drawBoxFill(phrase_entry, *entry_col);
  CAsset::drawBoxFill(syllab_entry, *entry_col);
  CAsset::drawBoxFill(define_entry, *entry_col);

  if (!phrasetext[0].empty() || write_target == W_PHRASE) {
    CSurface::OnDraw(phrasecanvas.canvas, phrasecanvas.canvR, phrase_entry);
  } else {
    SDL_Rect srcR = phrase_entry;
    srcR.x = srcR.y = 0;
    CSurface::OnDraw(infocanvas.canvas, srcR, phrase_entry);
  }

  if (!syllabarytext[0].empty() || write_target == W_SYLLAB) {
    CSurface::OnDraw(syllabarycanvas.canvas, syllabarycanvas.canvR, syllab_entry);
  } else {
    SDL_Rect srcR = syllab_entry;
    srcR.x = 0;
    srcR.y = phrase_entry.h;
    CSurface::OnDraw(infocanvas.canvas, srcR, syllab_entry);
  }

  if (!definetext[0].empty() || write_target == W_DEFINE) {
    CSurface::OnDraw(definecanvas.canvas, definecanvas.canvR, define_entry);
  } else {
    SDL_Rect srcR = define_entry;
    srcR.x = 0;
    srcR.y = phrase_entry.h + syllab_entry.h;
    CSurface::OnDraw(infocanvas.canvas, srcR, define_entry);
  }
}

void CCreate::OnCleanup() {
  phrasecanvas.cleanup();
  syllabarycanvas.cleanup();
  definecanvas.cleanup();
  infocanvas.cleanup();

  for (int i = 0; i < phrasetext.size(); i++) {
    phrasetext[i].clear();
  }
  for (int i = 0; i < syllabarytext.size(); i++) {
    syllabarytext[i].clear();
  }
  for (int i = 0; i < definetext.size(); i++) {
    definetext[i].clear();
  }

  phrasetext.clear();
  syllabarytext.clear();
  definetext.clear();
  candidatetext.clear();
}
