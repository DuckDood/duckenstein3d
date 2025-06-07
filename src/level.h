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

SDL_Rect rL[1] = {
 {554,258,215,318},
};

int color[1][3] = {
 {255,255,0},
};

circle cL[2] = {
 {286,374,28},
{1102,181,97},
};

int ccolor[2][3] = {
 {158,255,105},
{158,255,105},
};

triangle tL[5] = {
 { {132,603}, {320,542}, {347,636}, },
{ {412,300}, {298,86}, {298,86}, },
{ {220,216}, {416,189}, {337,291}, },
{ {956,352}, {1098,428}, {915,580}, },
{ {1036,694}, {1256,691}, {1036,534}, },
};

int tcolor[5][3] = {
 {158,45,255},
{158,45,255},
{158,45,255},
{158,45,255},
{158,45,255},
};
