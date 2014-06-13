#ifndef RBC_CKEYBOARD_H
#define RBC_CKEYBOARD_H

#include <SDL/SDL.h>
#include <vector>

class RBC_CKeyboard
{
	private:
		static std::vector<int> history; /**< The history of latest key presses */
		static SDL_Event event;		/**< Type made for catching events, especially keyboard ones */
		static bool lastkey[400];

		static bool keys[400];

		static void RBC_AddToHistory(int key);

	public:

		static int RBC_IsAnyKeyDown(void){if(event.type==SDL_KEYDOWN){return event.key.keysym.sym;}else{return 0;}}

		static bool RBC_KeyPressed(int key); /**< This method checks if concrete key (given as an argument) is pressed */

		static bool RBC_KeyDown(int key); /**< This method checks if concrete key (given as an argument) is down */

		static void RBC_Refresh(void){SDL_PollEvent(&event);if(event.type==SDL_KEYDOWN){keys[event.key.keysym.sym]=1;}else if(event.type==SDL_KEYUP){keys[event.key.keysym.sym]=0;lastkey[event.key.keysym.sym]=0;}} /**< Necessary function to grab an event */
};

#endif // RBC_CKEYBOARD_H
