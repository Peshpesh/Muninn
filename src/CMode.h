#ifndef _C_MODE_H_
#define _C_MODE_H_

enum app_module {
  APP_MODE_TITLE    , // application is at title screen
  APP_MODE_LESSON   , // lesson module
  APP_MODE_VOCAB    , // vocabulary module
  APP_MODE_GRAMMAR  , // grammar module
  APP_MODE_PRACTICE , // practice/testing module
  APP_MODE_NEW      , // module to add new content
  APP_MODE_STATS    , // statistics/progress page
  APP_MODE_OPTIONS  , // options page
};

class CMode {
private:
  static app_module handle;

public:
  CMode();

  // changes module handle
  static void setMode(app_module mode);

  // returns true if passed module is active
  static bool isModeOn(app_module mode);

  // returns active mode
  static app_module getMode();
  static app_module* getModeptr();
};

#endif
