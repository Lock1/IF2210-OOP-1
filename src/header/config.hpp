// 13519214
// Common preprocessor
#ifndef _CONFIG
#define _CONFIG

// Target macro
#ifdef _WINDOWS
#define CLEAR_SCREEN_CMD "cls"

#endif


#ifdef _LINUX
#define CLEAR_SCREEN_CMD "clear"

#endif


// Common configuration
// Use 2:1, x:y ratio for square-y map
#define MAP_MAX_X 50
#define MAP_MAX_Y 25





#endif
