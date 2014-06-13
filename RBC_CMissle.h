#ifndef RBC_CMISSLE_H
#define RBC_CMISSLE_H

#include <vector>
#include <string>
#include "RBC_CEngineFunctions.h"
#include "RBC_CXMLParser.h"
#include "RBC_CHitbox.h"

class RBC_CMissle{
	private:
		SDL_Surface* bitmap;
		std::vector<RBC_CHitbox> hitbox;
		int height;
		int speed;
		int damage;

		int number;

		int startframe;

		char charbuff[100];

	public:
		int x,y;

		int RBC_GetDamage(void){return damage;}

		int RBC_ReturnWidth(void){return bitmap->w;}

		int RBC_GetHeight(void){return height;}

		int RBC_GetSpeed(void){return speed;}

		int RBC_GetStartFrame(void){return startframe;}

		std::vector<RBC_CHitbox> RBC_GetHitboxes(void){return hitbox;}

		int RBC_GetHitboxesNumber(void){return hitbox.size();}

		SDL_Surface* RBC_GetBitmap(void){return bitmap;}

		RBC_CMissle(void){height=200; x=0;number=0;}

		void RBC_SetStartX(int xx){x=xx;for(int i=0; i<hitbox.size(); i++){hitbox[i].x+=xx;}}
		void RBC_SetStartY(int yy){y=yy;for(int i=0; i<hitbox.size(); i++){hitbox[i].y+=yy;}}

		void RBC_SetSpeed(int xx){speed=xx;}

		void RBC_MoveMissleRight(){
			x+=speed;
			for(int i=0; i<hitbox.size(); i++){hitbox[i].x+=speed;}
		}

		void RBC_MoveMissleLeft(){
			x-=speed;
			for(int i=0; i<hitbox.size(); i++){hitbox[i].x-=speed;}
		}

		void RBC_SetNumber(int no){number=no;}

		void RBC_LoadMissleXML(void);
		void RBC_LoadMissleBitmap(void);
};

#endif // RBC_CMISSLE_H
