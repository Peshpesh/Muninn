#ifndef _C_TITLE_H_
#define _C_TITLE_H_

#include "CMode.h"
#include "CEvent.h"
#include "CAsset.h"
#include "CType.h"
#include "CUtil.h"
#include "CSound.h"
#include "CMask.h"

#include "CConfig.h"

// #include "CIO.h"
#include "CTransition.h"

/*
  Selections to depict in the title screen/main menu:
    1. Lessons
    2. (Practice) Vocabulary & phrases
    3. (Practice) Grammar
    4. Practice & testing
    5. Add material
    6. Statistics
    7. Options

  Amongst these choices are stylistic additions, which
  could include a logo, title, version, disclaimer, etc.
*/

class CTitle : public CEvent {
  CTitle();

  // short menu_kind;
  // short pos;

public:
  static CTitle control;
  bool call_terminate;

private:
  app_module* transMode; // new mode to transition to from title menu

public:
  void OnInit();

  void OnEvent(SDL_Event* Event);

  void OnLoop();

  bool OnRender(const SDL_Point& p);

  void OnCleanup();

private:
  void OnKeyDown(SDL_Keycode sym, Uint16 mod);
  void OnLButtonDown(int mX, int mY);
};

namespace title {
  extern const SDL_Color* f_def;
  extern const SDL_Color* f_hov;
  extern const SDL_Color* f_lock;
  // extern const SDL_Point* o_def;
  // extern const SDL_Point* o_hov;
  // extern const SDL_Point* o_lock;

  extern const SDL_Rect r_lesson;
  extern const SDL_Rect r_vocab;
  extern const SDL_Rect r_grammar;
  extern const SDL_Rect r_practice;
  extern const SDL_Rect r_add;
  extern const SDL_Rect r_stats;

  extern const char* const t_lesson;
  extern const char* const t_vocab;
  extern const char* const t_grammar;
  extern const char* const t_practice;
  extern const char* const t_add;
  extern const char* const t_stats;

  extern const SDL_Point* c_lesson;
  extern const SDL_Point* c_vocab;
  extern const SDL_Point* c_grammar;
  extern const SDL_Point* c_practice;
  extern const SDL_Point* c_add;
  extern const SDL_Point* c_stats;

  // extern const short num_options;
  // extern const char* const opt_list[];
}

#endif
