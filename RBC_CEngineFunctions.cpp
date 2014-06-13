#include "RBC_CEngineFunctions.h"

#define FPSRATE 63
#define SCREENW 800
#define SCREENH 600

SDL_Surface* RBC_CEngineFunctions::screen;

long long int RBC_CEngineFunctions::frame;

char RBC_CEngineFunctions::charbuff[100];

SDL_Color RBC_CEngineFunctions::textColor;
TTF_Font* RBC_CEngineFunctions::font;


SDL_Surface* RBC_CEngineFunctions::loadedimg;
SDL_Surface* RBC_CEngineFunctions::optimizedimg;
SDL_Rect RBC_CEngineFunctions::offset;
SDL_Rect RBC_CEngineFunctions::shift;
SDL_Surface* RBC_CEngineFunctions::buff;
long long int RBC_CEngineFunctions::FPSStart;
long long int RBC_CEngineFunctions::FPSFinish;
int RBC_CEngineFunctions::LastSec;
int RBC_CEngineFunctions::LastFPS;
long long int RBC_CEngineFunctions::LastFrame;


bool RBC_CEngineFunctions::RBC_InitEverything(void){
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    screen=SDL_SetVideoMode(1024, 768, 32, SDL_SWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set video: %s\n", SDL_GetError());
        return 1;
    }
    if(TTF_Init()==-1){
			return 1;
    }

    SDL_WM_SetCaption( "Mordobicie", NULL );
    font=TTF_OpenFont("tahoma.ttf", 20);
    //TTF_SetFontOutline(font, 3);
    frame=0;
    if (!font){
        return 1;
    }

    textColor.r=255;
    textColor.g=0;
    textColor.b=0;
    FPSStart=0;
    FPSFinish=0;
    LastSec=0;
    LastFPS=FPSRATE;

    return 0;
}

void RBC_CEngineFunctions::RBC_NextLoop(void){
    frame++;
    RBC_SetFPS();
    LastFrame=SDL_GetTicks();
}

SDL_Surface* RBC_CEngineFunctions::RBC_LoadIMG(const char* name){
    loadedimg=IMG_Load(name);
    if(loadedimg==NULL){return NULL;}
    optimizedimg=SDL_DisplayFormatAlpha(loadedimg);
    SDL_FreeSurface(loadedimg);
    return optimizedimg;
}

void RBC_CEngineFunctions::RBC_BlitSurface(int x, int y, SDL_Surface *src){
    offset.x=x;
    offset.y=y;
    SDL_BlitSurface(src, NULL, screen, &offset);
}

void RBC_CEngineFunctions::RBC_BlitSurface(int x, int y, int xshift, SDL_Surface *src){
    offset.x=x;
    offset.y=y;
    if(shift.x+screen->w>src->w){

    	}else{
    shift.x=xshift;
    shift.y=0;
    shift.w=src->w;
    shift.h=src->h;
    	}
    SDL_BlitSurface(src, &shift, screen, &offset);
}

void RBC_CEngineFunctions::RBC_Write(int x, int y, const char* text){
    buff=TTF_RenderText_Solid(font, text, textColor);
    RBC_BlitSurface(x, y, buff);
    SDL_FreeSurface(buff);
}

void RBC_CEngineFunctions::RBC_Write(int x, int y, int number){
    buff=TTF_RenderText_Solid(font, itoa(number, charbuff, 10), textColor);
    RBC_BlitSurface(x, y, buff);
    SDL_FreeSurface(buff);
}

void RBC_CEngineFunctions::RBC_DrawRect(int x, int y, int w, int h, int r, int g, int b){
    offset.x=x;
    offset.y=y;
    offset.w=w;
    offset.h=h;
    SDL_FillRect(screen, &offset, SDL_MapRGB(screen->format, r, g, b));
}

int RBC_CEngineFunctions::RBC_GetFPS(void){
    if ((SDL_GetTicks()/1000)-LastSec){
        LastSec=SDL_GetTicks()/1000;
        LastFPS=FPSFinish-FPSStart;
        FPSStart=frame;
    }else{
        FPSFinish=frame;
    }
    return LastFPS;
}

void RBC_CEngineFunctions::RBC_SetFPS(void){
    if (SDL_GetTicks()-LastFrame<=(1000/FPSRATE)){
        SDL_Delay((1000/FPSRATE)-(SDL_GetTicks()-LastFrame));
    }
}

SDL_Surface* RBC_CEngineFunctions::RBC_FlipSurface(SDL_Surface* surface){
	SDL_Surface *flipped;
	flipped = SDL_CreateRGBSurface( SDL_SWSURFACE, surface->w, surface->h, surface->format->BitsPerPixel, surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask );
	if(SDL_MUSTLOCK(surface)){SDL_LockSurface( surface );}
	for(int x=0,rx=flipped->w-1; x<flipped->w; x++, rx--)
    {
        for( int y = 0, ry = flipped->h - 1; y < flipped->h; y++, ry-- )
        {
			Uint32 pixel = RBC_GetPixel32(surface, x, y);
			RBC_PutPixel32(flipped, rx, y, pixel);
        }
    }
    return flipped;
}

Uint32 RBC_CEngineFunctions::RBC_GetPixel32(SDL_Surface *surface, int x, int y)
{
	Uint32 *pixels = (Uint32 *)surface->pixels;
    return pixels[ ( y * surface->w ) + x ];
}

void RBC_CEngineFunctions::RBC_PutPixel32(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    Uint32 *pixels = (Uint32 *)surface->pixels;
    pixels[ ( y * surface->w ) + x ] = pixel;
}
