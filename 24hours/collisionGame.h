#ifndef _COLLISION__H
#define _COLISION__H

#include "processGame.h"

int collide2d(float x1, float y1, float x2, float y2, float wt1, float ht1, float wt2, float ht2);
void collisionDetect(GameState *game);

#endif // _COLLISION__H
