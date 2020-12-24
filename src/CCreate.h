#ifndef _C_CREATE_H_
#define _C_CREATE_H_

#include <math.h>
#include "CAsset.h"
#include "CCanvas.h"
#include "CEvent.h"
#include "CTransition.h"

class CCreate : public CEvent {

  CCreate();

public:
  static CCreate control;

private:
  CCanvas vocabspace;
  CCanvas furispace;
  CCanvas compspace;

  bool vocab_str;
  bool furi_str;
  SDL_Point p_A;
  SDL_Point p_B;

public:
  bool OnInit();
  void OnEvent(SDL_Event* Event);
  void OnLoop(const SDL_Point& p);
  void OnRender();

private:
  void OnLButtonDown(int mX, int mY);
  void OnLButtonUp(int mX, int mY);
};

namespace createcard {
  extern const short vocab_sz;
  extern const short furi_sz;
  extern const SDL_Point* str_col;
  extern const SDL_Rect vocab_line; // line containing the actual word/phrase
  extern const SDL_Rect furi_line;  // line containing furigana for kanji in vocab_line
  extern const SDL_Rect comp_line;  // the compound/combination of both lines
}

#endif
