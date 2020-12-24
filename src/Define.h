#ifndef _DEFINE_H_
#define _DEFINE_H_

#ifdef WIN32
#define WWIDTH 1366    // pixels
#define WHEIGHT 768    // pixels
#endif

#ifdef __ANDROID__
 #include <android/api-level.h>
#endif
#ifdef __ANDROID_API__
#define WWIDTH 1366    // pixels
#define WHEIGHT 768    // pixels
#endif

#define MAX_RGBA 255
#define MAX_VOLUME 128

/* "Escape Threshold":  amount of time the user has to hold down the ESC key  */
/*                      to terminate the application                          */
#define ESC_THRESH 1500 // milliseconds
#define PI 3.14159265

#endif
