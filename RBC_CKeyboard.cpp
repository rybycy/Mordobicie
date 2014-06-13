#include "RBC_CKeyboard.h"

std::vector<int> RBC_CKeyboard::history;
SDL_Event RBC_CKeyboard::event;
bool RBC_CKeyboard::lastkey[400];
bool RBC_CKeyboard::keys[400];

bool RBC_CKeyboard::RBC_KeyDown(int key){
	if(keys[key]){lastkey[key]=1;return 1;}
	return 0;

}

bool RBC_CKeyboard::RBC_KeyPressed(int key){
	if(keys[key] && !lastkey[key]){lastkey[key]=1;return 1;}
	return 0;
}


void RBC_CKeyboard::RBC_AddToHistory(int key){
	if(history.size()>=20){
			history.erase(history.begin());
		}

history.push_back(key);
}

