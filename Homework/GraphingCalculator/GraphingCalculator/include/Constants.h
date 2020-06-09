#ifndef CONSTANTS_H
#define CONSTANTS_H

const float SCREEN_WIDTH = 1600;
const float SCREEN_HEIGHT = 900;
const float WORK_PANEL = SCREEN_WIDTH * 4 / 5;
const float SIDE_BAR = SCREEN_WIDTH * 1 / 5;
const int SB_MOUSE_POSITION = 0;
const int SB_MOUSE_CLICKED = SB_MOUSE_POSITION + 1;
const int SB_KEY_PRESSED = SB_MOUSE_CLICKED + 1;
const float GRAPH_CENTER_X = (SCREEN_WIDTH - SIDE_BAR) / 2;
const float GRAPH_CENTER_Y = SCREEN_HEIGHT / 2;
const float GRAPH_WIDTH = SCREEN_WIDTH - SIDE_BAR;
const float GRAPH_HEIGHT = SCREEN_HEIGHT;
const int NUM_FUNCTIONS = 8;
const int NUM_SIDEBAR_ITEMS = 9;
const float BUTTON_X_PADDING = 8;
const double e = 2.71828;
const double pi = 3.14159;

#endif // CONSTANTS_H
