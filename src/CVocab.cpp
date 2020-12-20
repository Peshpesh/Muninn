#include "CVocab.h"

CVocab CVocab::control;

CVocab::CVocab() {
  group_option = vocab::GROUP_BY_TOPIC;
  at_menu = true;
}

void CVocab::OnInit() {
  at_menu = true;

  if (CTransition::control.okToTrans) {
    CTransition::control.okToTrans = false;
  }
  CType::control.SetColor(&rgb::black);
}

void CVocab::OnLoop() {
  CTransition::control.OnLoop();
}

void CVocab::OnCleanup() {

}
