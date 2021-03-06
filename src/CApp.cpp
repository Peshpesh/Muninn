#include "CApp.h"

/* The constructor initializes the Running Program flag */
CApp::CApp() {
  Win_Display = NULL;

  Running = true;

  cursor.x = cursor.y = 0;

  esc_init = 0;
}

/* This is the executable member that contains the program's
* critical functions. Initialization, event handling, data manipulation,
* rendering, and house keeping are done within this member.
*/
int CApp::OnExecute() {
  // If our initialization function fails, the program will end here.
  if (OnInit() == false) {
    return -1;
  }

  SDL_Event Event;
  // This loop will run endlessly until something makes the Running
  // flag false. That will happen, hopefully, by the user's decision.
  while (Running) {
    // Check for pending events; handle them
    while (SDL_PollEvent(&Event)) {
      OnEvent(&Event);
    }
    OnLoop();      // Perform necessary manipulations (gameplay)
    OnRender();    // Render updated info
  }
  OnCleanup();       // Clean up the program before exiting
  return 0;
}

int main(int argc, char* argv[]) {
  CApp game;
  return game.OnExecute();
}
