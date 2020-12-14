#include "CApp.h"

void CApp::OnCleanup() {
  SDL_DestroyWindow(Win_Display);

  CType::control.OnCleanup();
  CAsset::OnCleanup();
  CSurface::OnCleanup();
  // CGame::control.OnCleanup();

  SDL_Quit();
}
