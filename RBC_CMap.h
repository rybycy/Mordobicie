#ifndef RBC_CMap_H
#define RBC_CMap_H

#include <string>
#include "RBC_CEngineFunctions.h"

class RBC_CMap{
	private:
		SDL_Surface* bitmap;
		int width;
		std::string path;
		int number;

		static char charbuff[100];

		static int mapcounter;
	public:

		RBC_CMap(int x);
		RBC_CMap(void);

		void RBC_LoadBitmap(void);

		void RBC_Draw(int shift);

		void RBC_SetNumber(int x);

		int RBC_GetMapWidth(void){return bitmap->w;}

};

#endif
