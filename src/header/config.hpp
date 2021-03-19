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

#define MSG_MAX_X 40
#define MAX_MESSAGE 5 // TODO : Maybe not needed

// NOTE : Render coordinate (0, 0) starting from upper left corner
#define MAP_OFFSET_X 1
#define MAP_OFFSET_Y 1
#define MESSAGE_OFFSET_X MAP_OFFSET_X+MAP_MAX_X+5
#define MESSAGE_OFFSET_Y MAP_OFFSET_Y+1

#define CURSOR_REST_X 60
#define CURSOR_REST_Y 20

// Map Border, using compass direction,
// (ex. NW = connecting border from north and west direction)
#define MAP_BORDER_NE '\xC8'
#define MAP_BORDER_NW '\xBC'
#define MAP_BORDER_SE '\xC9'
#define MAP_BORDER_SW '\xBB'
#define MAP_BORDER_NS '\xBA'
#define MAP_BORDER_WE '\xCD'

// Message border
#define MSG_BORDER_NE '\xC0'
#define MSG_BORDER_NW '\xD9'
#define MSG_BORDER_SE '\xDA'
#define MSG_BORDER_SW '\xBF'
#define MSG_BORDER_NS '\xB3'
#define MSG_BORDER_WE '\xC4'

// Tiles
#define TILE_GRASS '\xB0'
#define TILE_SEA '\xB2'

// Map
#define SEA_STARTING_X 20
#define SEA_STARTING_Y 10


#endif
