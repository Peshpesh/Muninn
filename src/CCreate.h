#ifndef _C_CREATE_H_
#define _C_CREATE_H_

#include <math.h>
#include <vector>
#include "CAsset.h"
#include "CCanvas.h"
#include "CEvent.h"
#include "CTransition.h"

#include <SDL_ttf.h>

class CCreate : public CEvent {

  CCreate();

public:
  static CCreate control;

private:
  TTF_Font* bigfont;
  TTF_Font* smolfont;

  std::vector<std::string> phrasetext;     // UTF-8 strings of the card's phrase
  std::vector<std::string> syllabarytext;  // UTF-8 strings of the phrase's syllables
  std::vector<std::string> definetext;     // UTF-8 strings of phrase's definition/translation

  CCanvas phrasecanvas;
  CCanvas syllabarycanvas;
  CCanvas definecanvas;

  // SDL_Texture* phrasetexture;
  // SDL_Texture* syllabarytexture;
  SDL_Texture* candidatetexture;
  // SDL_Texture* definetexture;

  char write_target;

  SDL_Rect phraseR;
  SDL_Rect syllabaryR;
  SDL_Rect candidateR;
  SDL_Rect defineR;

public:
  bool OnInit();
  void OnEvent(SDL_Event* Event);
  void OnLoop(const SDL_Point& p);
  void OnRender();

private:
  void OnKeyDown(SDL_Keycode sym, Uint16 mod);
  void OnTextInput(char const* text);
  void OnTextEditing(char const* text, Sint32 start, Sint32 length);
  void OnLButtonDown(int mX, int mY);
  void OnLButtonUp(int mX, int mY);
};

namespace createcard {
  enum targets {
    W_PHRASE = 1,
    W_SYLLAB = 2,
    W_DEFINE = 3
  };

  // extern const short phrase_sz;
  // extern const short syllab_sz;
  extern const SDL_Point* str_col;
  extern const SDL_Rect phrase_entry; // line containing the actual word/phrase
  extern const SDL_Rect syllab_entry; // line containing kana-only vocab_line
  extern const SDL_Rect define_entry; // line containing definition

  extern const SDL_Rect save_button;
  extern const SDL_Rect clear_button;
}

#endif
