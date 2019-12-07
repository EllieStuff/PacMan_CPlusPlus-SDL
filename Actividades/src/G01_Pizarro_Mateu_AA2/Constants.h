#pragma once

const int MAP_WIDTH = 20;
const int MAP_HEIGHT = 20;
const int NUM_OF_TILES = 400;

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 700;
const int HUD_WIDTH = 200;
const int HUD_EDGES = 15;

const int FPS = 60;
const float DELAY_TIME = 1000.0f / FPS;
const int PIXELS_PER_FRAME = 7;
const int TILES_PIXEL = 35;

enum class SceneState { GO_TO_PLAY = 0, GO_TO_MENU, GO_TO_RANKING, GO_TO_EXIT, RUNNING_PLAY, RUNNING_MENU, RUNNING_RANKING, RUNNING_SPLASH_SCREEN, EXIT };

enum class MapTiles { WALL = 0, EMPTY, FRUIT, POWER_UP, POINTS, HUD };

enum class Direction { UP = 0, DOWN, RIGHT, LEFT, NONE };

enum EnemyType { ClYDE = 0, INKY, BLINKY };