#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <SDL2/SDL.h>

//#define WIN_WIDTH 320
//#define WIN_HEIGHT 180

#define res 1

#define SH WIN_HEIGHT
#define SW WIN_WIDTH




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
	case 0:
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

bool sqrcol(float x, float y, SDL_Rect rect) {
	if(x > rect.x && x < rect.x + rect.w /* X's done*/ && y > rect.y && y <rect.y+rect.h) {
		return true;
		// i know i can just return the boolean ^^ this is for debugging remind me to reyurn boolean
	}
	return false;
}

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
    

	float x = 300, y = 300;
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


		

        SDL_RenderClear(renderer);
		int tamnt=0;
		int tamntc = tamnt;
		//SDL_Rect top = {0,0,1366,1};
		//SDL_Rect bottom = {0,1665,1366, 12};
		float fra = a-50*0.01; // fr fr nocap a
		SDL_Rect r = {500, 500, 50, 50};
		SDL_Rect re = {800, 200, 120, 120};

		for(int i = 0; i<300; i++) {
		tamnt = tamntc - 300*0.01/3;
		//float dist = sqrt(pow(768,2) + pow(1366,2));
		float dist = 768;
		
		for(; ; tamnt++) {
			if(sqrcol(x+sin(fra)*tamnt, y+cos(fra)*tamnt, r) || sqrcol(x+sin(fra)*tamnt, y+cos(fra)*tamnt, re)/* || sqrcol(x+sin(fra)*tamnt, y+cos(fra)*tamnt, top) || sqrcol(x+sin(fra)*tamnt, y+cos(fra)*tamnt, bottom)*/) {
				if(tamnt==-1) {
					x=lastX;
					y=lastY;
				}
				SDL_Rect rect = {i*5, (768-(dist-tamnt))/2, 5, fmax(dist-tamnt, 0)};
				//SDL_SetRenderDrawColor(renderer, ((float)tamnt/(float)255)*255, 0, 0, 255);
				//SDL_SetRenderDrawColor(renderer, fmin(dist(x, y, x+sin(fra)*tamnt, 255), y+cos(fra)*tamnt  ) , 0, 0, 255);
				

				

				SDL_SetRenderDrawColor(renderer, fmax(255*fmin(1-(float)tamnt/768, 255), 0), 0, 0, 255);


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
				SDL_Rect rect = {i*5, (768-(dist-tamnt))/2, 5, fmax(dist-tamnt, 0)};
				SDL_SetRenderDrawColor(renderer, fmax(255*fmin(1-(float)tamnt/768, 255), 0), 0, 0, 255);
				
				//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
				//SDL_RenderFillRect(renderer, &rect);
				SDL_RenderFillRect(renderer, &rect);
				//tamnt;
				break;
			}
		}
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		//SDL_RenderDrawLine(renderer, x, y, x + sin(fra)*tamnt, y + cos(fra)*tamnt);
		fra+=0.01/3;

		}
        //SDL_RenderCopy(renderer, texture, NULL, NULL);
		
		//SDL_RenderDrawRect(renderer, &r);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderPresent(renderer);
    }

    //SDL_DestroyRenderer(renderer);
    //SDL_DestroyWindow(window);
    //SDL_Quit();
	// these are causing free() invalid pointer for some reason

    return 0;
}

