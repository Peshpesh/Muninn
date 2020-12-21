#ifndef _C_TRANSITION_H_
#define _C_TRANSITION_H_

#include "CCanvas.h"
#include "CAsset.h"
#include "Define.h"

enum {
  TRANS_WIPE = 0,
};

class CTransition {
  CTransition();

private:
  CCanvas transMask; // a working canvas texture for complex transitions

private:
  int init_reset_time;
  int init_delay_time;

private:
  int fadeout_timer;
  int fadein_timer;
  int delay_timer;
  int last_time;
  int transtype;

public:
  bool okToTrans;

private:
  const SDL_Point* color;

public:
  static CTransition control;

  bool OnInit();

  void reqTrans(const int& transtype, const SDL_Point* palcol);
  void reqReset();
  bool isActive();

  void transDone();

  void OnLoop();

  void OnRender();

private:
  void blank();
  void wipeout();
  void wipein();
  void checkerout();
  void checkerin();
};

#endif
