#pragma once

const int MAP_WIDTH = 20;
const int MAP_HEIGHT = 20;
const int NUM_OF_TILES = 400;

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 700;
const int HUD_WIDTH = 200;
const int HUD_EDGES = 15;
const int RANKING_EDGES = 30;

const int FPS = 30;
const float DELAY_TIME = 1500.0f / FPS;
const int PIXELS_PER_FRAME = 7;
const int TILES_PIXEL = 35;
const int SPLASH_SCREEN_TIME = 3000;
const int POWER_UP_TIME = 10000;
const int FRUITS_FIRST_DELAY = 10000;
const int FRUITS_DELAY = 15000;
const int MAX_LIVES = 3;
const int POWER_UP_EXTRA_SCORE = 20;
const int MAX_SCORE = 9999;
const int MAX_FRUITS = 9;
const int RANKING_CAPACITY = 5;
const int NAME_MAX_SIZE = 12;

enum class SceneState { GO_TO_PLAY = 0, GO_TO_MENU, GO_TO_RANKING, GO_TO_EXIT, RUNNING_PLAY, RUNNING_MENU, RUNNING_RANKING, RUNNING_SPLASH_SCREEN, EXIT };

enum class MapTiles { EMPTY = 0, EMPTY_P_UP, WALL, POWER_UP, POINTS, HUD};

enum class FruitTypes { CHERRY = 0, STRAWBERRY, ORANGE, COUNT, EMPTY };

enum class Direction { UP = 0, DOWN, RIGHT, LEFT, NONE };

enum ButtonPosition { PLAY_SOUND = 0, RANKING_EXIT, MENU_SOUND, MENU_PLAY, MENU_RANKING, MENU_EXIT, COUNT };

enum EnemyType { ClYDE = 0, INKY, BLINKY };