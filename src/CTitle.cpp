#include "CTitle.h"

CTitle CTitle::control;

CTitle::CTitle() {
  call_terminate = false;
  OnInit();
}

void CTitle::OnInit() {
  // menu_kind = Title::MAIN;
  // pos = 0;
  if (CTransition::control.activated) {
    CTransition::control.activated = false;
  }
  CType::control.SetColor(&rgb::black);
}

void CTitle::OnLoop() {
  CTransition::control.OnLoop();
}

void CTitle::OnCleanup() {

}
