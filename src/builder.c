#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <SDL2/SDL.h>

//#define WIN_WIDTH 320
//#define WIN_HEIGHT 180

#ifndef res
#define res 10
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

void drawTri(SDL_Renderer *renderer, triangle t) {
	SDL_RenderDrawLine(renderer, t.p1.x, t.p1.y, t.p2.x, t.p2.y);
	SDL_RenderDrawLine(renderer, t.p2.x, t.p2.y, t.p3.x, t.p3.y);
	SDL_RenderDrawLine(renderer, t.p3.x, t.p3.y, t.p1.x, t.p1.y);
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
/*	if(x > rect.x && x < rect.x + rect.w  && y > rect.y && y <rect.y+rect.h) {
		return true;
		// i know i can just return the boolean ^^ this is for debugging remind me to reyurn boolean
	}
	return false;
	*/
	return x > rect.x && x < rect.x + rect.w  && y > rect.y && y <rect.y+rect.h;
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
    

	//float x = 300, y = 300;
	float x = 10, y = 10;
	float a = 0;
	int r = 255;
	int g = 0;
	int b = 0;
	int lasy;
	int lasg;
	bool ong = false;

	int lasr;
	bool onr = false;

	int lasb;
	bool onb = false;


	//uint8_t pixels[WIN_WIDTH * WIN_HEIGHT*4];
	//uint8_t *pixels = malloc(WIN_WIDTH*WIN_HEIGHT*4);
	//for(int i = 0; i < WIN_WIDTH*WIN_HEIGHT; i++) {
	//	pixel(i, 0, 8, pixels);
	//}

    // main loop
    bool should_quit = false;
	int lastX = x, lastY = y;
		int amnt = 0;
		int amnt2 = 0;
		int amnt3 = 0;
		SDL_Rect *rList = malloc(sizeof(SDL_Rect)*amnt);
		int *cList1 = malloc(sizeof(int)*amnt);
		int *cList2 = malloc(sizeof(int)*amnt);
		int *cList3 = malloc(sizeof(int)*amnt);



		circle *cList = malloc(sizeof(circle)*amnt2);


		int *ccList1 = malloc(sizeof(int)*amnt2);
		int *ccList2 = malloc(sizeof(int)*amnt2);
		int *ccList3 = malloc(sizeof(int)*amnt2);

		triangle *tList = malloc(sizeof(triangle)*amnt3);

		int *tcList1 = malloc(sizeof(int)*amnt3);
		int *tcList2 = malloc(sizeof(int)*amnt3);
		int *tcList3 = malloc(sizeof(int)*amnt3);

    SDL_Event e;
	bool mousePrevDown = false;
		bool ic = false;
		bool it = false;
		int tc = -1;
		float2 tmppoints[3] = {
			{0,0},
			{0,0},
			{0,0}
		};
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
		//SDL_Rect r = {500, 500, 50, 50};
		//SDL_Rect re = {800, 200, 120, 120};
		SDL_Rect ui1 = {0,0,20,5};
		int curX, curY;
		int cornerX, cornerY;
		SDL_Rect tmpRect = {0, 0, 0, 0};
		circle tmpc = {0, 0, 0};
		triangle tmpt = { {0, 0}, {0, 0}, {0, 0} };
		
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

		if(!keys[5]) {
			
		if(!keys[KEY_A]) {
	
		if(!keys[2] && !ic ) {
		
		if(SDL_BUTTON(SDL_GetMouseState(&curX, &curY)) == 1 && !mousePrevDown) {
			cornerX = curX;
			cornerY = curY;
			mousePrevDown = true;
			
		} else if(SDL_BUTTON(SDL_GetMouseState(&curX, &curY)) == 1 ) {
			tmpRect = (SDL_Rect){cornerX, cornerY, curX-cornerX, curY-cornerY};
			if(curX-cornerX > 0 &&
			curY-cornerY > 0)  {
			//SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			SDL_RenderDrawRect(renderer, &tmpRect);
			}
		}
		else if(mousePrevDown){
			mousePrevDown = false;
			rList = realloc(rList, (1+amnt)*sizeof(SDL_Rect));
			cList1 = realloc(cList1, (1+amnt)*sizeof(int));
			cList2 = realloc(cList2, (1+amnt)*sizeof(int));
			cList3 = realloc(cList3, (1+amnt)*sizeof(int));
			if(curX-cornerX > 0 &&
			curY-cornerY > 0)  {
			rList[amnt] = (SDL_Rect){cornerX, cornerY, curX-cornerX, curY-cornerY};
			cList1[amnt] = r;
			cList2[amnt] = g;
			cList3[amnt] = b;
			amnt++;
			}
		}
		} else {
				ic=true;
			if(SDL_BUTTON(SDL_GetMouseState(&curX, &curY)) == 1 && !mousePrevDown) {
				mousePrevDown=true;
				cornerX = curX;
				cornerY = curY;
			} else if (SDL_BUTTON(SDL_GetMouseState(&curX, &curY)) == 1) {
				tmpc = (circle){cornerX, cornerY, dist(cornerX, cornerY, curX, curY)};
				DrawCircle(renderer, tmpc.x, tmpc.y, tmpc.r);
				
			} else if(mousePrevDown) {
				mousePrevDown = false;
				ic=false;


				// oh boy i hate c mem management
				// got realloc(clist1) mixed up with realloc(cclist1) and stuff
				ccList1 = realloc(ccList1, (1+amnt2)*sizeof(int));
				ccList2 = realloc(ccList2, (1+amnt2)*sizeof(int));
				ccList3 = realloc(ccList3, (1+amnt2)*sizeof(int));
				cList = realloc(cList, (1+amnt2)*sizeof(circle));

				ccList1[amnt2] = r;
				ccList2[amnt2] = g;
				ccList3[amnt2] = b;

				
				cList[amnt2].x = cornerX;
				cList[amnt2].y = cornerY;
				cList[amnt2].r = dist(cornerX, cornerY, curX, curY);
				amnt2++;
			}



		}


		} else {
			if(SDL_BUTTON(SDL_GetMouseState(&curX, &curY)) == 1 && !mousePrevDown) {
				mousePrevDown = true;
			} else if(SDL_BUTTON(SDL_GetMouseState(&curX, &curY)) == 1) {
				
			} else if(mousePrevDown) {
				//SDL_Log("hello");
				mousePrevDown = false;
				tc++;
				SDL_Log("%d", tc);
				tmppoints[tc] = (float2){curX, curY};
				if(tc==2) {
					tc = -1;
					tcList1 = realloc(tcList1, (1+amnt3)*sizeof(int));
					tcList2 = realloc(tcList2, (1+amnt3)*sizeof(int));
					tcList3 = realloc(tcList3, (1+amnt3)*sizeof(int));
					tList = realloc(tList, (1+amnt3)*sizeof(triangle));

					tList[amnt3].p1 = tmppoints[0];
					tList[amnt3].p2 = tmppoints[1];
					tList[amnt3].p3 = tmppoints[2];

					tcList1[amnt3] = r;
					tcList2[amnt3] = g;
					tcList3[amnt3] = b;

					amnt3++;
				}
			}
			
		}

		for(int i = 0; i<amnt; i++) {
			//SDL_Log("%d, %d, %d", cList1[i], cList2[i], cList3[i]);
			SDL_SetRenderDrawColor(renderer, cList1[i], cList2[i], cList3[i], 255);
			SDL_RenderDrawRect(renderer, &rList[i]);
		}
		for(int i = 0; i<amnt2; i++) {
			//SDL_Log("%d, %d, %d", cList1[i], cList2[i], cList3[i]);
			//SDL_SetRenderDrawColor(renderer, cList1[i], cList2[i], cList3[i], 255);
			SDL_SetRenderDrawColor(renderer, ccList1[i], ccList2[i], ccList3[i], 255);
			DrawCircle(renderer, cList[i].x, cList[i].y, cList[i].r);
		}
		for(int i = 0; i<amnt3; i++) {
			//SDL_Log("%d, %d, %d", cList1[i], cList2[i], cList3[i]);
			//SDL_SetRenderDrawColor(renderer, cList1[i], cList2[i], cList3[i], 255);
			SDL_SetRenderDrawColor(renderer, tcList1[i], tcList2[i], tcList3[i], 255);
			drawTri(renderer, tList[i]);
		}



		} else {
			SDL_Rect red = {100, 300, 100, 100};
			SDL_Rect green = {300, 300, 100, 100};
			SDL_Rect blue = {500, 300, 100, 100};
			SDL_Rect all = {700, 300, 100, 100};

			if(SDL_BUTTON(SDL_GetMouseState(&curX, &curY)) == 1 ) {
			if(!keys[6]) {
			if(sqrcol(curX, curY, red)) {
				r++;
			}
			if(sqrcol(curX, curY, green)) {
				g++;
			}
			if(sqrcol(curX, curY, blue)) {
				b++;
			}
			} else {

			if(sqrcol(curX, curY, red)) {
				r--;
			}
			if(sqrcol(curX, curY, green)) {
				g--;
			}
			if(sqrcol(curX, curY, blue)) {
				b--;
			}
			}

			}

			if (g > 255) g = 255;
			if (g < 0) g = 0;
			if (r > 255) r = 255;
			if (r < 0) r = 0;
			if (b > 255) b = 255;
			if (b < 0) b = 0;
			SDL_SetRenderDrawColor(renderer, r, 0, 0, 255);

			SDL_RenderFillRect(renderer, &red);

			SDL_SetRenderDrawColor(renderer, 0, g, 0, 255);

			SDL_RenderFillRect(renderer, &green);

			SDL_SetRenderDrawColor(renderer, 0, 0, b, 255);

			SDL_RenderFillRect(renderer, &blue);
			
			SDL_SetRenderDrawColor(renderer, r, g, b, 255);

			SDL_RenderFillRect(renderer, &all);
		}

		//SDL_RenderDrawLine(renderer, x, y, x + sin(fra)*tamnt, y + cos(fra)*tamnt);

        //SDL_RenderCopy(renderer, texture, NULL, NULL);
		
		//SDL_RenderDrawRect(renderer, &r);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderPresent(renderer);
    

	}

    //SDL_DestroyRenderer(renderer);
    //SDL_DestroyWindow(window);
    //SDL_Quit();
	// these are causing free() invalid pointer for some reason

	printf("SDL_Rect rL[%d] = {\n ", amnt);
	for(int i = 0; i<amnt; i++) {
		SDL_Rect cR = rList[i];
		printf("{%d,%d,%d,%d},\n", cR.x, cR.y, cR.w, cR.h);
	}
	printf("};\n\n");
	
	printf("int color[%d][3] = {\n ", amnt);
	for(int i = 0; i<amnt; i++) {
		printf("{%d,%d,%d},\n", cList1[i], cList2[i], cList3[i]);
	}
	printf("};\n\n");

	printf("circle cL[%d] = {\n ", amnt2);
	for(int i = 0; i<amnt2; i++) {
		circle cR = cList[i];
		printf("{%d,%d,%d},\n", (int)cR.x, (int)cR.y, (int)cR.r);
	}
	printf("};\n\n");


	printf("int ccolor[%d][3] = {\n ", amnt2);
	for(int i = 0; i<amnt2; i++) {
		circle cR = cList[i];
		printf("{%d,%d,%d},\n", ccList1[i], ccList2[i], ccList3[i]);
	}
	printf("};\n\n");

	printf("triangle tL[%d] = {\n ", amnt3);
	for(int i = 0; i<amnt3; i++) {
		triangle tR = tList[i];
		printf("{ {%d,%d}, {%d,%d}, {%d,%d}, },\n", (int)tR.p1.x, (int)tR.p1.y, (int)tR.p2.x, (int)tR.p2.y, (int)tR.p3.x, (int)tR.p3.y);
	}
	printf("};\n\n");


	printf("int tcolor[%d][3] = {\n ", amnt2);
	for(int i = 0; i<amnt3; i++) {
		triangle tR = tList[i];
		printf("{%d,%d,%d},\n", tcList1[i], tcList2[i], tcList3[i]);
	}
	printf("};\n\n");

    return 0;
}

