#include "RBC_CMap.h"

char RBC_CMap::charbuff[100];

int RBC_CMap::mapcounter;


RBC_CMap::RBC_CMap(int x){
	number=x;
}

RBC_CMap::RBC_CMap(void){
	number=0;
}

void RBC_CMap::RBC_SetNumber(int x){
	number=x;
}

void RBC_CMap::RBC_LoadBitmap(void){
	path="data/maps/Map";
	path+=itoa(number, charbuff, 10);
	path+=".png";
	mapcounter++;
	printf("Trying to load bitmap from %s ...\n", path.c_str());

	bitmap=RBC_CEngineFunctions::RBC_LoadIMG(path.c_str());
	width=bitmap->w;

	if(bitmap){printf("DONE\n");}
}

void RBC_CMap::RBC_Draw(int shift){
	RBC_CEngineFunctions::RBC_BlitSurface(0, 0, shift, bitmap);
}
