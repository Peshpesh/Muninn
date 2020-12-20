#include "CTitle.h"

CTitle CTitle::control;

CTitle::CTitle() {
  call_terminate = false;
  transMode = NULL;
  OnInit();
}

void CTitle::OnInit() {
  // menu_kind = Title::MAIN;
  // pos = 0;
  if (CTransition::control.okToTrans) {
    CTransition::control.okToTrans = false;
  }
  CType::control.SetColor(&rgb::black);
}

void CTitle::OnCleanup() {

}
