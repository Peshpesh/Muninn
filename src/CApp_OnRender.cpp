#include "CApp.h"

void CApp::OnRender() {
  static bool DEBUG = true;

  CSurface::Clear();

  if (CMode::isFlagOn(APP_MODE_MAIN)) {
    // CGame::control.OnRender();
  } else if (CMode::isFlagOn(APP_MODE_TITLE)) {
    CTitle::control.OnRender(cursor);
  }

  if (!CTransition::control.OnRender()) {
    // ERROR
  }

  if (DEBUG) {
    SDL_SysWMinfo info;
    SDL_VERSION(&info.version); /* initialize info structure with SDL version info */

    if(SDL_GetWindowWMInfo(Win_Display,&info)) { /* the call returns true on success */
      /* success */
      const char *subsystem = "an unknown system!";
      switch(info.subsystem) {
        case SDL_SYSWM_UNKNOWN:   break;
        case SDL_SYSWM_WINDOWS:   subsystem = "Microsoft Windows(TM)";  break;
        case SDL_SYSWM_X11:       subsystem = "X Window System";        break;
#if SDL_VERSION_ATLEAST(2, 0, 3)
        case SDL_SYSWM_WINRT:     subsystem = "WinRT";                  break;
#endif
        case SDL_SYSWM_DIRECTFB:  subsystem = "DirectFB";               break;
        case SDL_SYSWM_COCOA:     subsystem = "Apple OS X";             break;
        case SDL_SYSWM_UIKIT:     subsystem = "UIKit";                  break;
#if SDL_VERSION_ATLEAST(2, 0, 2)
        case SDL_SYSWM_WAYLAND:   subsystem = "Wayland";                break;
        case SDL_SYSWM_MIR:       subsystem = "Mir";                    break;
#endif
#if SDL_VERSION_ATLEAST(2, 0, 4)
        case SDL_SYSWM_ANDROID:   subsystem = "Android";                break;
    #endif
#if SDL_VERSION_ATLEAST(2, 0, 5)
        case SDL_SYSWM_VIVANTE:   subsystem = "Vivante";                break;
#endif
      }

      SDL_Log("This program is running SDL version %d.%d.%d on %s",
              (int)info.version.major,
              (int)info.version.minor,
              (int)info.version.patch,
              subsystem);

      SDL_version compiled, linked;
      SDL_VERSION(&compiled);
      SDL_GetVersion(&linked);
      // printf("We compiled against SDL version %d.%d.%d ...\n",
      //        compiled.major, compiled.minor, compiled.patch);
      // printf("But we are linking against SDL version %d.%d.%d.\n",
      //        linked.major, linked.minor, linked.patch);

      std::string comp_ver = CUtil::intToStr(compiled.major) + "."
                             + CUtil::intToStr(compiled.minor) + "."
                             + CUtil::intToStr(compiled.patch);

      using namespace gen;
      CType::control.SetOpacity(MAX_RGBA);
      CType::Write(quit_msg_f, comp_ver.c_str(), quit_msg_p, quit_msg_c);

      // int ms_sdl = 0;
      // int ms_orig = 0;
      // CAsset::test_a(ms_sdl, ms_orig);
      // std::string ms_sdl_str = CUtil::intToStr(ms_sdl);
      // std::string ms_orig_str = CUtil::intToStr(ms_orig);
      // const SDL_Point tmp = {10,20};
      // CType::Write(quit_msg_f, ms_sdl_str.c_str(), quit_msg_p, quit_msg_c);
      // CType::Write(quit_msg_f, ms_orig_str.c_str(), tmp, quit_msg_c);
    } else {
      /* call failed */
      SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Couldn't get window information: %s", SDL_GetError());
    }
  }

  // if (DEBUG) {
  //   std::string fps_str = CUtil::intToStr(CFPS::FPSControl.GetFPS()) + " fps";
  //   std::string speedfactor_str = CUtil::doubleToStr(CFPS::FPSControl.GetSpeedFactor(),10) + " SF";
  //   const SDL_Point fps_pos = {1,1};
  //   const SDL_Point sf_pos = {100,1};
  //   CType::Write(FONT_MINI, fps_str.c_str(), fps_pos, &rgb::white);
  //   CType::Write(FONT_MINI, speedfactor_str.c_str(), sf_pos, &rgb::white);
  // }

  if (esc_init) drawQuitMsg();

  CSurface::Present();
}

void CApp::drawQuitMsg() {
  using namespace gen;
  int msg_A = ((double)(SDL_GetTicks() - esc_init) / ESC_THRESH) * MAX_RGBA;
  if (CType::control.SetOpacity(msg_A)) {
    CType::Write(quit_msg_f, quit_msg, quit_msg_p, quit_msg_c);
  }
  CType::control.SetOpacity(MAX_RGBA);
}
