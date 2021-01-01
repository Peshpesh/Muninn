#ifndef _C_CREATE_H_
#define _C_CREATE_H_

#include <math.h>
#include <vector>
#include "CAsset.h"
#include "CCanvas.h"
#include "CEvent.h"
#include "CTransition.h"
#include "CText.h"

#include "CVocabcard.h"

class CCreate : public CEvent {

  CCreate();

public:
  static CCreate control;

private:
  CVocabcard card; // working vocab-card struct for creation

  std::vector<std::string> phrasetext;     // UTF-8 strings of the card's phrase
  std::vector<std::string> syllabarytext;  // UTF-8 strings of the phrase's syllables
  std::vector<std::string> definetext;     // UTF-8 strings of phrase's definition/translation

  std::string candidatetext;

  short phrasefont;
  short syllabaryfont;
  short definefont;

  CCanvas phrasecanvas;
  CCanvas syllabarycanvas;
  CCanvas definecanvas;
  CCanvas infocanvas;

  short info_alpha;

  char write_target;
  bool update_target;

  SDL_Rect candidateR; // rendering dimensions for the candidate string

public:
  bool OnInit();
  void OnEvent(SDL_Event* Event);
  void OnLoop();
  void OnRender();
  void OnCleanup();

private:
  void OnKeyDown(SDL_Keycode sym, Uint16 mod);
  void OnTextInput(char const* text);
  void OnTextEditing(char const* text, Sint32 start, Sint32 length);
  void OnLButtonDown(int mX, int mY);
  void OnLButtonUp(int mX, int mY);

private:
  void updateEntry(std::vector<std::string> *text, const short& fontID, CCanvas& canvobj, const SDL_Rect& entryR);

};

namespace createcard {
  enum targets {
    W_PHRASE = 1,
    W_SYLLAB = 2,
    W_DEFINE = 3
  };
  extern const SDL_Color* bg_col;
  extern const SDL_Point* str_col;
  extern const SDL_Color* entry_col;
  extern const SDL_Rect phrase_entry; // line containing the actual word/phrase
  extern const SDL_Rect syllab_entry; // line containing kana-only vocab_line
  extern const SDL_Rect define_entry; // line containing definition

  extern const SDL_Color* txt_col;
  extern const SDL_Color* edit_col;

  // the term can be:
  // 1. noun
  // 2. pronoun
  // 3. adjective
  // 4. verb
  // 5. adverb
  // 6. conjunction
  // 7. preposition
  // 8. phrase

  // adjectives can be i-, na-, or irregular types.
  // verbs can be u-, ru-, or irregular types.
  // any term can be formal, casual, or slang.

  // #1: identify what kind of term is being added
  // #2: if it's an adjective or verb, what specific type is it (if specified)?
  // #3: is the term formal, casual, slang, or unspecified?

  extern const SDL_Rect type_button;

  extern const SDL_Rect save_button;
  extern const SDL_Rect clear_button;
}

#endif
