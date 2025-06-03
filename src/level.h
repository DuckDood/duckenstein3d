#include <SDL2/SDL.h>
typedef struct circle {
	float x;
	float y;
	float r;
} circle;

typedef struct float2 {
	float x;
	float y;
}
float2;

typedef struct triangle {
	float2 p1;
	float2 p2;
	float2 p3;
} triangle;

SDL_Rect rL[2] = {
 {366,223,288,392},
{865,227,265,339},
};

int color[2][3] = {
 {255,0,0},
{255,0,0},
};

circle cL[1] = {
 {767,403,114},
};

int ccolor[1][3] = {
 {255,0,0},
};

triangle tL[0] = {
 };

int tcolor[0][3] = {
 };
