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

#define MSG_MAX_X 30
#define MSG_MAX_Y 10

#define MAX_MESSAGE 5

// NOTE : Render coordinate (0, 0) starting from upper left corner
#define MAP_OFFSET_X 1
#define MAP_OFFSET_Y 1
#define MESSAGE_OFFSET_X MAP_OFFSET_X+MAP_MAX_X+5
#define MESSAGE_OFFSET_Y MAP_OFFSET_Y



#endif
