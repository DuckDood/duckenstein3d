//#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "level.h"

//#define WIN_WIDTH 320
//#define WIN_HEIGHT 180

#ifndef res
#define res 10
#endif


#ifndef debug
#define debug 0
#endif

#define SH WIN_HEIGHT
#define SW WIN_WIDTH




// https://discourse.libsdl.org/t/query-how-do-you-draw-a-circle-in-sdl2-sdl2/33379
    void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius)
    {
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
    // Each of the following renders an octant of the circle
    SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
    SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
    SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
    SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
    SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
    SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
    SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
    SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

      if (error <= 0)
      {
      	++y;
      	error += ty;
      	ty += 2;
      }

      if (error > 0)
      {
      	--x;
      	tx += 2;
      	error += (tx - diameter);
      }

    }
    }





bool keys[7] = {false, false, false ,false, false, false, false};

enum Keys {
	KEY_W=0,
	KEY_A=1,
	KEY_S=2,
	KEY_D=3,
};

float dist(float x1, float y1, float x2, float y2) {
	return sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
}


/*
void pixel(int x, int y, int c, uint8_t *pixels) {
	if(y > WIN_HEIGHT-1) {
		y = WIN_HEIGHT-1;
	}
	if(x > WIN_WIDTH-1) {
		x = WIN_WIDTH-1;
	}

	switch(c) {
	cae 0:
	pixels[(y*WIN_WIDTH + x) * 4+0] = 255; pixels[(y*WIN_WIDTH + x) * 4+1] = 255; pixels[(y*WIN_WIDTH + x) * 4+2] = 0; pixels[(y*WIN_WIDTH + x) * 4+3] = 255; // yellow
	break;
	case 1:
	pixels[(y*WIN_WIDTH + x) * 4+0] = 160; pixels[(y*WIN_WIDTH + x) * 4+1] = 160; pixels[(y*WIN_WIDTH + x) * 4+2] = 0; pixels[(y*WIN_WIDTH + x) * 4+3] = 255; // dark yellow
	break;
	case 2:
	pixels[(y*WIN_WIDTH + x) * 4+0] = 0; pixels[(y*WIN_WIDTH + x) * 4+1] = 255; pixels[(y*WIN_WIDTH + x) * 4+2] = 0; pixels[(y*WIN_WIDTH + x) * 4+3] = 255; // green
	break;
	case 3:
	pixels[(y*WIN_WIDTH + x) * 4+0] = 255; pixels[(y*WIN_WIDTH + x) * 4+1] = 160; pixels[(y*WIN_WIDTH + x) * 4+2] = 0; pixels[(y*WIN_WIDTH + x) * 4+3] = 255; // dark green
	break;
	case 4:
	pixels[(y*WIN_WIDTH + x) * 4+0] = 0; pixels[(y*WIN_WIDTH + x) * 4+1] = 255; pixels[(y*WIN_WIDTH + x) * 4+2] = 255; pixels[(y*WIN_WIDTH + x) * 4+3] = 255; // cyan
	break;
	case 5:
	pixels[(y*WIN_WIDTH + x) * 4+0] = 0; pixels[(y*WIN_WIDTH + x) * 4+1] = 160; pixels[(y*WIN_WIDTH + x) * 4+2] =160; pixels[(y*WIN_WIDTH + x) * 4+3] = 255; // dark cyan
	break;
	case 6:
	pixels[(y*WIN_WIDTH + x) * 4+0] = 160; pixels[(y*WIN_WIDTH + x) * 4+1] = 100; pixels[(y*WIN_WIDTH + x) * 4+2] = 0; pixels[(y*WIN_WIDTH + x) * 4+3] = 255; // brown
	break;
	case 7:
	pixels[(y*WIN_WIDTH + x) * 4+0] = 50; pixels[(y*WIN_WIDTH + x) * 4+1] = 110; pixels[(y*WIN_WIDTH + x) * 4+2] = 0; pixels[(y*WIN_WIDTH + x) * 4+3] = 255; // dark brown
	break;
	case 8:
	pixels[(y*WIN_WIDTH + x) * 4+0] = 0; pixels[(y*WIN_WIDTH + x) * 4+1] = 60; pixels[(y*WIN_WIDTH + x) * 4+2] = 130; pixels[(y*WIN_WIDTH + x) * 4+3] = 255; // background
	break;
	}
}

void clearBackground() 
{int x,y;
 for(y=0;y<SH;y++)
 {
  for(x=0;x<SW;x++){ pixel(x,y,8, pixels);} //clear background color
 }	
}

*/

/*
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
} triangle;*/

bool sqrcol(float x, float y, SDL_Rect rect) {
/*	if(x > rect.x && x < rect.x + rect.w  && y > rect.y && y <rect.y+rect.h) {
		return true;
		// i know i can just return the boolean ^^ this is for debugging remind me to reyurn boolean
	}
	return false;
	*/
	return x > rect.x && x < rect.x + rect.w  && y > rect.y && y <rect.y+rect.h;
}

bool circol(float x, float y, circle c) {
	if(dist(x, y, c.x, c.y) < c.r) {
		return true;
		// i know i can just return the boolean ^^ this is for debugging remind me to reyurn boolean
	}
	return false;
}

float dot(float2 p1, float2 p2) {
	return p1.x*p2.x + p1.y*p2.y;
}
float2 perp(float2 p) {
	p = (float2){p.y, -p.x};
	return p;
}

bool pOnRs(float2 p1, float2 p2, float2 pp) {
	float2 ap = {pp.x-p1.x, pp.y-p1.y};
	float2 aa = perp((float2){p2.x - pp.x, p2.y-pp.y});
	return dot(ap, aa)>=0;
}

bool tricol(float x, float y, triangle t) {
	bool ab = pOnRs(t.p1, t.p2, (float2){x, y});
	bool ac = pOnRs(t.p2, t.p3, (float2){x, y});
	bool ad = pOnRs(t.p3, t.p1, (float2){x, y});
	return ab == ac && ac == ad;	
}

void drawTri(SDL_Renderer *renderer, triangle t) {
	SDL_RenderDrawLine(renderer, t.p1.x, t.p1.y, t.p2.x, t.p2.y);
	SDL_RenderDrawLine(renderer, t.p2.x, t.p2.y, t.p3.x, t.p3.y);
	SDL_RenderDrawLine(renderer, t.p3.x, t.p3.y, t.p1.x, t.p1.y);
}

// chat is it bad to define structs in #if???
#if debug == 1 
	struct ray {
		int x1;
		int y1;
		int x2;
		int y2;
	};
typedef struct ray ray;


void drawray(SDL_Renderer *renderer, ray r) {
		SDL_RenderDrawLine(renderer, r.x1, r.y1, r.x2, r.y2);
};

ray re[300];
#endif


int main(int argc, char **argv) {
	//The music that will be played
Mix_Music *music = NULL;

//The sound effects that will be used
Mix_Chunk *scratch = NULL;
Mix_Chunk *high = NULL;
Mix_Chunk *med = NULL;
Mix_Chunk *low = NULL;


    // SDL init

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

	

    // create SDL window
    SDL_Window *window = SDL_CreateWindow("light2d",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
		1366, 768,
        SDL_WINDOW_SHOWN);
    if (window == NULL) {
        SDL_Log("Unable to create window: %s", SDL_GetError());
        return 1;
    }

    // create renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        SDL_Log("Unable to create renderer: %s", SDL_GetError());
        return 1;
    }

	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
	{
		SDL_Log("Unable to start SDL2_Mixer: %s", SDL_GetError());
		return 1;
	}
	music = Mix_LoadMUS("doom gate.mp3");

	if(music == NULL) {
		SDL_Log("Unable to load music: %s", SDL_GetError());
		return -1;
	}
	Mix_PlayMusic(music, -1);
    

	//float x = 300, y = 300;
	float x = 10, y = 10;
	float a = 0;
	float tspeed = 1;
	//uint8_t pixels[WIN_WIDTH * WIN_HEIGHT*4];
	//uint8_t *pixels = malloc(WIN_WIDTH*WIN_HEIGHT*4);
	//for(int i = 0; i < WIN_WIDTH*WIN_HEIGHT; i++) {
	//	pixel(i, 0, 8, pixels);
	//}

    // main loop
    bool should_quit = false;
	int lastX = x, lastY = y;
    SDL_Event e;
	float vbob = 0;
	float z = 0;
	float rectYoff = sin(vbob);
    while (!should_quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                should_quit = true;
				continue;
            }
			
			if(e.type == SDL_KEYDOWN) {
				switch(e.key.keysym.sym) {
						case SDLK_w:
							keys[0]=true;
							break;
						case SDLK_a:
							keys[1]=true;
							break;
						case SDLK_s:
							keys[2]=true;
							break;
						case SDLK_d:
							keys[3]=true;
							break;
						case SDLK_m:
							keys[4]=true;
							break;

						case SDLK_COMMA:
							keys[5]=true;
							break;
						case SDLK_PERIOD:
							keys[6]=true;
							break;
					}

			}
			if(e.type == SDL_KEYUP) {
					switch(e.key.keysym.sym) {
						case SDLK_w:
							keys[0]=false;
							break;
						case SDLK_a:
							keys[1]=false;
							break;
						case SDLK_s:
							keys[2]=false;
							break;
						case SDLK_d:
							keys[3]=false;
							break;
						case SDLK_m:
							keys[4]=false;
							break;

						case SDLK_COMMA:
							keys[5]=false;
							break;
						case SDLK_PERIOD:
							keys[6]=false;
							break;
					}
			}
        }
		lastX = x;
		lastY = y;

	

		if(keys[KEY_W]) {
			//y+=10;
			x+=sin(a)*10*tspeed;
			y+=cos(a)*10*tspeed;
			vbob+=0.28;
		}

		if(keys[KEY_S]) {
			//y-=10;
			x-=sin(a)*10*tspeed;
			y-=cos(a)*10*tspeed;
			vbob+=0.28;
		}

		if(keys[KEY_A]) {
			//x-=10;
			a-=0.04*tspeed;
		}

		if(keys[KEY_D]) {
			//x+=10;
			a+=0.04*tspeed;
		}

		if(keys[5]) {
			x-=cos(a)*5*tspeed;
			y+=sin(a)*5*tspeed;
		}
		if(keys[6]) {
			x+=cos(a)*5*tspeed;
			y-=sin(a)*5*tspeed;
		}

		if(keys[4]) {
			tspeed = 0.3;
		} else {
			tspeed = 1;
		}

		rectYoff = sin(vbob) > 0? sin(vbob)*20+20 + z : sin(vbob)*17+20 + z;


		

        SDL_RenderClear(renderer);
		int tamnt=0;
		int tamntc = tamnt;

		float fra = a-50*0.01; // fr fr nocap a
							   //
							   //

/*
		SDL_Rect rL[12] = {
 {250,273,89,116},
{338,274,84,115},
{417,272,84,117},
{487,272,89,117},
{565,269,95,120},
{653,271,92,117},
{741,272,76,114},
{796,274,100,112},
{869,275,121,111},
{975,276,87,110},
{1055,277,83,109},
{1123,279,92,107},
};

int color[12][3] = {
 {255,2,0},
{255,73,0},
{255,255,0},
{140,255,0},
{0,255,0},
{0,255,118},
{0,255,255},
{0,0,255},
{125,0,255},
{255,0,255},
{255,0,114},
{255,0,0},
};

circle cL[7] = {
 {341,138,55},
{1124,537,68},
{687,525,0},
{683,530,69},
{672,140,65},
{1041,148,62},
{321,523,73},
};

int ccolor[7][3] = {
 {255,255,255},
{255,255,255},
{186,182,177},
{186,182,177},
{186,182,177},
{89,88,75},
{89,88,75},
};*/
/*
		SDL_Rect rL[4] = {
 {314,49,35,76},
{63,287,79,82},
{108,220,64,48},
{128,78,28,22},
};

int color[4][3] = {
 {255,0,0},
{255,0,0},
{255,0,0},
{255,0,0},
};

circle cL[2] = {
 {177,177,173},
{303,281,138},
};

int ccolor[2][3] = {
 {255,0,0},
{255,0,0},
};

triangle tL[] = {
	{ {10 + 100, 10 + 100}, {20 + 100, 100 + 100}, {50 + 100, 50 + 100} },
	{ {700, 700}, {600, 700}, {650,600} },
};
int tcolor[][3] = {
	{0, 255, 255},
	{0, 255, 255},
};

*/

		/*
SDL_Rect rL[6] = {
 {449,253,310,310},
{309,244,70,102},
{1214,463,116,154},
{853,414,60,72},
{283,452,63,83},
{179,137,39,100},
};

int color[6][3] = {
 {255,0,0},
{255,0,0},
{255,0,226},
{255,0,226},
{255,0,226},
{164,67,152},
};

circle cL[8] = {
 {961,321,87},
{598,230,92},
{94,332,3},
{143,316,0},
{123,249,0},
{133,373,65},
{139,601,54},
{459,694,104},
};

int ccolor[8][3] = {
 {255,0,0},
{255,0,226},
{164,67,152},
{164,67,152},
{164,67,152},
{164,67,152},
{164,67,152},
{164,67,152},
};

triangle tL[6] = {
 { {954,661}, {978,648}, {949,580}, },
{ {247,507}, {303,641}, {186,610}, },
{ {196,366}, {210,410}, {201,402}, },
{ {804,184}, {882,184}, {847,159}, },
{ {1249,342}, {1141,294}, {1217,277}, },
{ {664,671}, {696,642}, {685,631}, },
};

int tcolor[8][3] = {
 {255,0,0},
{255,0,0},
{255,0,0},
{255,0,226},
{255,0,226},
{164,67,152},
};

*/





bool circ = false;
bool tri = false;



		for(int i = 0; i<300; i++) {
		tamnt = tamntc - 300*0.01/3;
		//float dist = sqrt(pow(768,2) + pow(1366,2));
		float dist = 768;
		float falloff;
		//float dist = 1366;
		bool col = false;
		int cIndex;
		
		for(; ; tamnt+=res) {
			if(tamnt > dist) break;
			for(int i = 0; i<sizeof(rL)/sizeof(SDL_Rect); i++)
			{
				if(sqrcol(x+sin(fra)*tamnt, y+cos(fra)*tamnt, rL[i])/* || circol(x+sin(fra)*tamnt, y+cos(fra)*tamnt, c)*/) {
					col = true;
					cIndex = i;
					// steps back after collisions (nearly same result as increasing res, except corners are slightly rounded)
					// circol works but i am too lazy too put them somewhere (i need to put it in the builder)
					for(;sqrcol(x+sin(fra)*tamnt, y+cos(fra)*tamnt, rL[i])/* || circol(x+sin(fra)*tamnt, y+cos(fra)*tamnt, c)*/;) {
						tamnt--;

					}
					break;
					
				}
			}
			for(int i = 0; i<sizeof(cL)/sizeof(circle); i++)
			{
				if(/*sqrcol(x+sin(fra)*tamnt, y+cos(fra)*tamnt, rL[i]) || */circol(x+sin(fra)*tamnt, y+cos(fra)*tamnt, cL[i])) {
					col = true;
					circ = true;
					cIndex = i;
					// steps back after collisions (nearly same result as increasing res, except corners are slightly rounded)
					// circol works but i am too lazy too put them somewhere (i need to put it in the builder)
					for(;/*sqrcol(x+sin(fra)*tamnt, y+cos(fra)*tamnt, rL[i]) || */circol(x+sin(fra)*tamnt, y+cos(fra)*tamnt, cL[i]);) {
						tamnt--;

					}
					break;
					
				}
			}

			for(int i = 0; i<sizeof(tL)/sizeof(triangle); i++) 
			{

				if(tricol(x+sin(fra)*tamnt, y+cos(fra)*tamnt, tL[i])) {
					col = true;
					tri = true;
					cIndex = i;
					for(;tricol(x+sin(fra)*tamnt, y+cos(fra)*tamnt, tL[i]);) {
						tamnt--;
	
					}
					break;
					// colors no working because
					// duh
					// thats 23 lines below this
				}

			}

			//if(sqrcol(x+sin(fra)*tamnt, y+cos(fra)*tamnt, r) || sqrcol(x+sin(fra)*tamnt, y+cos(fra)*tamnt, re)/* || sqrcol(x+sin(fra)*tamnt, y+cos(fra)*tamnt, top) || sqrcol(x+sin(fra)*tamnt, y+cos(fra)*tamnt, bottom)*/) {
			if(col/* || sqrcol(x+sin(fra)*tamnt, y+cos(fra)*tamnt, top) || sqrcol(x+sin(fra)*tamnt, y+cos(fra)*tamnt, bottom)*/) {
				col = false;
				if(tamnt<1) {
					x=lastX;
					y=lastY;
				}
				int height = fmax(dist-tamnt, 0);
				SDL_Rect rect = {i*4.5-5, (rectYoff) + (float)(768-(height))/2, 5, height};
				//SDL_SetRenderDrawColor(renderer, ((float)tamnt/(float)255)*255, 0, 0, 255);
				//SDL_SetRenderDrawColor(renderer, fmin(dist(x, y, x+sin(fra)*tamnt, 255), y+cos(fra)*tamnt  ) , 0, 0, 255);
				

				

				//SDL_SetRenderDrawColor(renderer, fmax(255*fmin(1-(float)tamnt/768, 255), 0), 0, 0, 255);
				if(circ) {
				circ = false;
				SDL_SetRenderDrawColor(renderer, fmax( ccolor[cIndex][0] *fmin(1-(float)tamnt/768, 255), 0), fmax( ccolor[cIndex][1]  *fmin(1-(float)tamnt/768, 255), 0), fmax(  ccolor[cIndex][2]  *fmin(1-(float)tamnt/768, 255), 0), 255);
				} else if (tri){
				tri = false;
				SDL_SetRenderDrawColor(renderer, fmax( tcolor[cIndex][0] *fmin(1-(float)tamnt/768, 255), 0), fmax( tcolor[cIndex][1]  *fmin(1-(float)tamnt/768, 255), 0), fmax(  tcolor[cIndex][2]  *fmin(1-(float)tamnt/768, 255), 0), 255);
				}
				else {
				SDL_SetRenderDrawColor(renderer, fmax( color[cIndex][0] *fmin(1-(float)tamnt/768, 255), 0), fmax( color[cIndex][1]  *fmin(1-(float)tamnt/768, 255), 0), fmax(  color[cIndex][2]  *fmin(1-(float)tamnt/768, 255), 0), 255);
				}

				//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
				

				//SDL_SetRenderDrawColor(renderer, fmax(fmin(768-tamnt, 255), 0), 0, 0, 255);
				//SDL_SetRenderDrawColor(renderer, fmax(fmin(768-tamnt, 255), 0), 0, 0, 255);
				SDL_RenderFillRect(renderer, &rect);
				break;
			}

			if(x + sin(fra)*tamnt > 1366 || x + sin(fra)*tamnt < 0 || y + cos(fra)*tamnt > 768 || y + cos(fra)*tamnt < 0) {
				if(tamnt<1) {
					x=lastX;
					y=lastY;
				}
				//tamnt-=1;
				//SDL_Rect rect = {i, 0, 1, 768-tamnt};
				int height= fmax(dist-tamnt, 0);
				SDL_Rect rect = {i*4.5-5, (rectYoff) + (float)(768-(height))/2, 5, height};
				SDL_SetRenderDrawColor(renderer, fmax(255*fmin(1-(float)tamnt/768, 255), 0), 0, 0, 255);
				
				//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
				//SDL_RenderFillRect(renderer, &rect);
				SDL_RenderFillRect(renderer, &rect);
				//tamnt;
				break;
			}
		}
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		#if debug == 1
		re[i] = (ray){x, y, x + sin(fra)*tamnt, y + cos(fra)*tamnt};
		//SDL_RenderDrawLine(renderer, x, y, x + sin(fra)*tamnt, y + cos(fra)*tamnt);
		#endif
		fra+=0.01/(3);

		}
        //SDL_RenderCopy(renderer, texture, NULL, NULL);
		
		//SDL_RenderDrawRect(renderer, &r);
		
	#if debug == 1
		for(int i = 0; i<sizeof(rL)/sizeof(SDL_Rect); i++) {
			SDL_RenderDrawRect(renderer, &rL[i]);
		}

		for(int i = 0; i<sizeof(cL)/sizeof(circle); i++) {
			DrawCircle(renderer, cL[i].x, cL[i].y, cL[i].r);
		}

		for(int i = 0; i<sizeof(tL)/sizeof(triangle); i++) {
			drawTri(renderer, tL[i]);
		}

		for(int i = 0; i<300; i++) {
			drawray(renderer, re[i]);
		}


	#endif

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderPresent(renderer);
    }

    //SDL_DestroyRenderer(renderer);
    //SDL_DestroyWindow(window);
    //SDL_Quit();
	// these are causing free() invalid pointer for some reason

    return 0;
}

