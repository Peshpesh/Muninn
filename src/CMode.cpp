#include "CMode.h"

app_module CMode::handle = APP_MODE_TITLE;

CMode::CMode() {
  //
}

void CMode::setMode(app_module mode) {
  handle = mode;
}

bool CMode::isModeOn(app_module mode) {
  return (mode == handle);
}

app_module CMode::getMode() {
  return handle;
}

app_module* CMode::getModeptr() {
  return &handle;
}
