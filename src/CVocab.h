#ifndef _C_VOCAB_H_
#define _C_VOCAB_H_

#include "CMode.h"
#include "CEvent.h"
#include "CAsset.h"
#include "CType.h"
#include "CUtil.h"
#include "CSound.h"
#include "CMask.h"

#include "CConfig.h"

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

class CVocab : public CEvent {
  CVocab();

public:
  static CVocab control;

  bool at_menu;
  short group_option;

public:
  void OnInit();

  void OnEvent(SDL_Event* Event);

  void OnRender(const SDL_Point& p);

  void OnLoop();

  void OnCleanup();

private:
  void OnKeyDown(SDL_Keycode sym, Uint16 mod);
  void OnLButtonDown(int mX, int mY);
};

namespace vocab {
  extern const SDL_Color* f_def;
  extern const SDL_Color* bg_hue;

  extern const SDL_Rect r_options[];
  extern const char* const t_options[];
  extern const SDL_Point* c_options;
  enum {
    GROUP_BY_TOPIC    = 0,
    GROUP_BY_LESSON   = 1,
    GROUP_BY_FAMILIAR = 2,
    GROUP_BY_FREQ     = 3,
    GROUP_BY_JLPT     = 4,
    GROUP_BY_ALPHA    = 5
  }; // grouping options
}

#endif
