#include "CApp.h"

bool CApp::OnInit() {
  CError::handler.OnInit();

  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    CError::handler.ReportSDLErr("FATAL => SDL_Init failed");
    return false;
  }

  if ((Win_Display = SDL_CreateWindow(
                      "Project Muninn v0.0",
                      SDL_WINDOWPOS_CENTERED,
                      SDL_WINDOWPOS_CENTERED,
                      WWIDTH,
                      WHEIGHT,
                      SDL_WINDOW_SHOWN)) == NULL)
  {
    CError::handler.ReportErr("FATAL => SDL_CreateWindow failed.");
    return false;
  }

  if (!CSurface::OnInit(Win_Display)) {
    CError::handler.ReportErr("FATAL => CSurface failed to initialize.");
    return false;
  }

  if (!CAsset::OnInit()) {
    CError::handler.ReportErr("FATAL => CAsset failed to initialize.");
    return false;
  }

  if (!CType::control.OnInit()) {
    CError::handler.ReportErr("FATAL => CType failed to initialize.");
    return false;
  }

  if (!CTransition::control.OnInit()) {
    CError::handler.ReportErr("FATAL => CTransition failed to initialize.");
    return false;
  }

  if (!CCreate::control.OnInit()) {
    CError::handler.ReportErr("FATAL => CCreate failed to initialize.");
    return false;
  }

  // if (!CGameIO::control.init()) {
  //   CError::handler.ReportErr("FATAL => CGameIO failed to initialize.");
  //   return false;
  // }

  active_mode = CMode::getModeptr();

  return true;
}
