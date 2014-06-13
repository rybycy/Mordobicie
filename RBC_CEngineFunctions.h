#ifndef RBC_CEngineFunctions_h
#define RBC_CEngineFunctions_h

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#define LIMITER 1001

class RBC_CEngineFunctions{
		private:
			static SDL_Surface* screen; 	/** Screen surface **/

			static long long int frame;		/** Integer type variable to count loop number **/

			static SDL_Color textColor; 	/** Structure for storing RGB color informations**/
			static TTF_Font *font; 			/** Base font for project**/

			static char charbuff[100];  	/** Function-supporting array **/

			static SDL_Surface* optimizedimg;
			static SDL_Surface* loadedimg; 	/** Buffer struct for image optimization**/
			static SDL_Rect shift;			/** An argument for map displacement **/
			static SDL_Rect offset;			/** Object made for being an argument in functions**/
			static SDL_Surface *buff;		/** Buffer struct for rendering text **/

			static long long int FPSStart;	/** Integer which stores number of loops in the beginning of second**/
			static long long int FPSFinish;	/** Integer which stores number of loops in every point drawing near end**/
			static int LastSec;				/** Determinant of last second**/
			static int LastFPS;				/** Integer of FPS in last second**/
			static long long int LastFrame;	/** In every loop it equals SDL_GetTicks() function. It is necessary in RBC_SetFPS() to delay image properly.**/

		public:
			static bool RBC_InitEverything(void); /** Initialization of video, screen surface and font **/

			static SDL_Surface* RBC_FlipSurface(SDL_Surface* x); /**< Flip surface by Y */

			static int RBC_Abs(int x){if(x>0){return x;}else{return -x;}}

			static Uint32 RBC_GetPixel32(SDL_Surface *surface, int x, int y); /**< Assisting function for flipping */

			static void RBC_PutPixel32(SDL_Surface *surface, int x, int y, Uint32 pixel); /**< Assisting function for flipping */

			static void RBC_NextLoop(void); /** Executes all steps needed to set fps **/

			static int RBC_GetScreenW(void){return screen->w;}

			static int RBC_GetScreenH(void){return screen->h;}

			static int RBC_GetTicks(void){return SDL_GetTicks();} /**< Return time in 0.001 sec unit */

			static SDL_Surface* RBC_LoadIMG(const char* name); /** Function of loading optimized images**/

			static void RBC_BlitSurface(int x, int y, SDL_Surface *src); /** Method for blitting image with easy calling**/

			static void RBC_BlitSurface(int x, int y, int xshift, SDL_Surface *src); /** Overloaded method for blitting image with easy calling, made especially for map**/

			static void RBC_Write(int x, int y, const char* text);	/** Method of writing text in const char format on the screen. It uses global font**/

			static void RBC_Write(int x, int y, int number); /** Overloaded version of function for writing numbers on the screen**/

			static void RBC_DrawRect(int x, int y, int w, int h, int r, int g, int b); /** Function for drawing a rectangle made for easy calling**/

			static void RBC_Flip(void){SDL_Flip(screen);} /** Method for applying image in the end of loop**/

			static void RBC_ClearScreen(void){SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 50, 50, 50));} /** Clear screen function**/

			static int RBC_GetFPS(void); /** A method which shows frames count in last second.**/

			static void RBC_SetFPS(void); /** Function which locks frames per second according to FPSRATE definition **/
};

#endif
