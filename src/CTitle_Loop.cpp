#include "CTitle.h"

void CTitle::OnLoop() {
  if (transMode && CTransition::control.okToTrans) {
    CMode::setMode(*transMode);
    delete transMode;
    CTransition::control.transDone();
  }
}
