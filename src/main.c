#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <SDL2/SDL.h>

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

typedef struct circle {
	float x;
	float y;
	float r;
} circle;

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
    // SDL init
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
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
    

	//float x = 300, y = 300;
	float x = 10, y = 10;
	float a = 0;
	//uint8_t pixels[WIN_WIDTH * WIN_HEIGHT*4];
	//uint8_t *pixels = malloc(WIN_WIDTH*WIN_HEIGHT*4);
	//for(int i = 0; i < WIN_WIDTH*WIN_HEIGHT; i++) {
	//	pixel(i, 0, 8, pixels);
	//}

    // main loop
    bool should_quit = false;
	int lastX = x, lastY = y;
    SDL_Event e;
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
			x+=sin(a)*10;
			y+=cos(a)*10;
		}

		if(keys[KEY_S]) {
			//y-=10;
			x-=sin(a)*10;
			y-=cos(a)*10;
		}

		if(keys[KEY_A]) {
			//x-=10;
			a-=0.04;
		}

		if(keys[KEY_D]) {
			//x+=10;
			a+=0.04;
		}

		if(keys[5]) {
			x-=cos(a)*5;
			y+=sin(a)*5;
		}
		if(keys[6]) {
			x+=cos(a)*5;
			y-=sin(a)*5;
		}


		

        SDL_RenderClear(renderer);
		int tamnt=0;
		int tamntc = tamnt;
		//SDL_Rect top = {0,0,1366,1};
		//SDL_Rect bottom = {0,1665,1366, 12};
		float fra = a-50*0.01; // fr fr nocap a
		//SDL_Rect r = {500, 500, 50, 50};
		//SDL_Rect re = {800, 200, 120, 120};
		/*SDL_Rect rL[] = {
			{500, 500, 50, 50},
			{800, 200, 120, 120}
		};*/
		/*
SDL_Rect rL[8] = {
 {138,0,92,598},
{342,387,67,380},
{209,0,500,180},
{393,697,419,70},
{589,154,116,415},
{857,148,364,40},
{990,176,72,320},
{806,685,559,82},
};
*//*
SDL_Rect rL[2] = {
 {263,167,1,480},
{264,168,297,2},
};

int color[8][8] = {
	{255, 0, 0},
	{255, 0, 0},
	{255, 0, 0},
	{255, 0, 0},
	{255, 0, 0},
	{0, 255, 255},
	{0, 255, 255},
	{255, 0, 0},
};*/
/*

SDL_Rect rL[9] = {
 {160,0,106,532},
{434,365,118,402},
{243,0,518,145},
{718,102,62,475},
{515,663,265,104},
{773,672,361,95},
{774,642,28,40},
{1000,264,107,255},
{911,207,296,106},
};

int color[9][3] = {
{255,0,0},
{255,0,0},
{255,0,0},
{255,0,0},
{255,0,0},
{255,0,0},
{255,0,0},
{0,200,198},
{0,200,198},
};*/


		



SDL_Rect rL[8] = {
 {454,325,85,194},
{279,362,166,156},
{729,433,218,189},
{671,345,134,74},
{567,205,128,66},
{723,345,229,71},
{555,489,129,102},
{413,281,153,73},
};

int color[8][3] = {
 {255,0,0},
{255,0,0},
{255,0,0},
{255,0,0},
{255,0,0},
{255,217,255},
{255,217,255},
{255,217,27},
};

circle cL[5] = {
 {311,283,96},
{353,364,0},
{195,493,77},
{1096,468,89},
{867,253,125},
};

int ccolor[5][3] = {
 //{255,0,0},
 {0,55500,0},
{255,217,255},
{255,217,255},
{255,217,255},
{255,217,27},
};


		



bool circ = false;



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

			//if(sqrcol(x+sin(fra)*tamnt, y+cos(fra)*tamnt, r) || sqrcol(x+sin(fra)*tamnt, y+cos(fra)*tamnt, re)/* || sqrcol(x+sin(fra)*tamnt, y+cos(fra)*tamnt, top) || sqrcol(x+sin(fra)*tamnt, y+cos(fra)*tamnt, bottom)*/) {
			if(col/* || sqrcol(x+sin(fra)*tamnt, y+cos(fra)*tamnt, top) || sqrcol(x+sin(fra)*tamnt, y+cos(fra)*tamnt, bottom)*/) {
				col = false;
				if(tamnt<1) {
					x=lastX;
					y=lastY;
				}
				SDL_Rect rect = {i*4.5-5, (768-(dist-tamnt))/2, 5, fmax(dist-tamnt, 0)};
				//SDL_SetRenderDrawColor(renderer, ((float)tamnt/(float)255)*255, 0, 0, 255);
				//SDL_SetRenderDrawColor(renderer, fmin(dist(x, y, x+sin(fra)*tamnt, 255), y+cos(fra)*tamnt  ) , 0, 0, 255);
				

				

				//SDL_SetRenderDrawColor(renderer, fmax(255*fmin(1-(float)tamnt/768, 255), 0), 0, 0, 255);
				if(circ) {
				circ = false;
				SDL_SetRenderDrawColor(renderer, fmax( ccolor[cIndex][0] *fmin(1-(float)tamnt/768, 255), 0), fmax( ccolor[cIndex][1]  *fmin(1-(float)tamnt/768, 255), 0), fmax(  ccolor[cIndex][2]  *fmin(1-(float)tamnt/768, 255), 0), 255);
				} else {
				SDL_SetRenderDrawColor(renderer, fmax( color[cIndex][0] *fmin(1-(float)tamnt/768, 255), 0), fmax( color[cIndex][1]  *fmin(1-(float)tamnt/768, 255), 0), fmax(  color[cIndex][2]  *fmin(1-(float)tamnt/768, 255), 0), 255);
				}

				//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
				

				//SDL_SetRenderDrawColor(renderer, fmax(fmin(768-tamnt, 255), 0), 0, 0, 255);
				//SDL_SetRenderDrawColor(renderer, fmax(fmin(768-tamnt, 255), 0), 0, 0, 255);
				SDL_RenderFillRect(renderer, &rect);
				break;
			}

			if(x + sin(fra)*tamnt > 1366 || x + sin(fra)*tamnt < 0 || y + cos(fra)*tamnt > 768 || y + cos(fra)*tamnt < 0) {
				if(tamnt==-1) {
					x=lastX;
					y=lastY;
				}
				//tamnt-=1;
				//SDL_Rect rect = {i, 0, 1, 768-tamnt};
				SDL_Rect rect = {i*4.5-5, (768-(dist-tamnt))/2, 5, fmax(dist-tamnt, 0)};
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

