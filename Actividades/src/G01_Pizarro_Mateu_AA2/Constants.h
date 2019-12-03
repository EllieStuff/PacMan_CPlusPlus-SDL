#pragma once

const int MAP_WIDTH = 20;
const int MAP_HEIGHT = 20;
const int NUM_OF_TILES = 400;

const int FPS = 60;
const float DELAY_TIME = 1000.0f / FPS;

enum class SceneState { GO_TO_PLAY = 0, GO_TO_MENU, GO_TO_RANKING, GO_TO_EXIT, RUNNING, EXIT };

enum class MapTiles { WALL = 0, VOID, FRUIT, POWER_UP, POINTS };

enum class Direction { UP = 0, DOWN, RIGHT, LEFT };

enum EnemyType { Clyde = 0, Inky, Blinky };