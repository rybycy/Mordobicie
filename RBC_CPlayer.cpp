#include "RBC_CPlayer.h"

RBC_CPlayer::RBC_CPlayer(void){
	hero=NULL;
	movementlength=0;
	x=50;
	y=300;
	hppercent=100;
	dealt=0;
	facedirection=0;
	leftdifference=0;
	winctr=0;
	lastmissle=-1000;
}

void RBC_CPlayer::RBC_DrawHero(void){
	RBC_CEngineFunctions::RBC_BlitSurface(x+(facedirection?leftdifference:0), y, hero->RBC_Draw(facedirection, actualstate.state, actualstate.value,framenumber));
}

void RBC_CPlayer::RBC_SetButton(int akey, int astate, int avalue){
	statekey.push_back(0);
	statekey[statekey.size()-1].key=akey;
	statekey[statekey.size()-1].state=astate;
	statekey[statekey.size()-1].value=avalue;
}

void RBC_CPlayer::RBC_PushBackMissle(void){
	if(RBC_CEngineFunctions::RBC_GetTicks()-lastmissle>1000){
		lastmissle=RBC_CEngineFunctions::RBC_GetTicks();
		printf("Pushan backan misslan on %i\n", lastmissle);
		missle.push_back(hero->RBC_GetMissle());

		if(!facedirection){missle[missle.size()-1].RBC_SetStartX(x + hero->RBC_Draw(facedirection, actualstate.state, actualstate.value, framenumber)->w);}
		else{missle[missle.size()-1].RBC_SetStartX(x);}

		missle[missle.size()-1].RBC_SetStartY(y);
	}
}

bool RBC_CPlayer::RBC_IsReadyToThrow(void){
	if(RBC_CEngineFunctions::RBC_GetTicks()-lastmissle>1000){return 1;}
	else{return 0;}
}

void RBC_CPlayer::RBC_ChangeHeroStatus(int astate, int avalue){
    if(!(actualstate.state==astate && actualstate.value==avalue)){
		if(!actualstate.state && actualstate.value==7){
			if(framenumber>=hero->RBC_GetFramesCount(actualstate.state, actualstate.value)){
				actualstate.state=0;
				actualstate.value=0;
			}
		}else
		if(!astate && avalue==7){
			if(!actualstate.state && actualstate.value==4){
				y=300;
			}

			printf("Changing hero status from state: %i - %i, value: %i - %i\n", actualstate.state, astate, actualstate.value, avalue);
			actualstate.state=0;
			actualstate.value=7;
			movementlength=0;
			dealt=0;
			framenumber=0;
			if(facedirection){leftdifference=hero->RBC_GetTheWidestBitmap()-hero->RBC_Draw(facedirection, actualstate.state, actualstate.value,framenumber)->w;}
		}else
		if(actualstate.state==0 && actualstate.value==4){
			if(!astate && !avalue){actualstate.state=0;actualstate.value=0;}
			else if(!astate && avalue){
				if(astate==0 && avalue==1){x+=10;}
				else if(astate==0 && avalue==2){x-=10;}
			}
		}
		else if((actualstate.state==1 || actualstate.state==2) && (astate || avalue)){

		}else if(!astate && avalue==6){
			if(RBC_IsReadyToThrow()){
			actualstate.state=astate;
			actualstate.value=avalue;
			movementlength=0;
			dealt=0;
			framenumber=0;
			if(facedirection){leftdifference=hero->RBC_GetTheWidestBitmap()-hero->RBC_Draw(facedirection, actualstate.state, actualstate.value,framenumber)->w;}
			}
		}
		else{
			printf("Changing hero status from state: %i - %i, value: %i - %i\n", actualstate.state, astate, actualstate.value, avalue);
			actualstate.state=astate;
			actualstate.value=avalue;
			movementlength=0;
			dealt=0;
			framenumber=0;
			if(facedirection){leftdifference=hero->RBC_GetTheWidestBitmap()-hero->RBC_Draw(facedirection, actualstate.state, actualstate.value,framenumber)->w;}
		}
    }
}

void RBC_CPlayer::RBC_Attack(RBC_CPlayer* victim){
	if(!dealt){
		victim->RBC_HurtHero(RBC_GetActualDamage());
		dealt=1;
	}
	victim->RBC_ChangeHeroStatus(0,7);
}

void RBC_CPlayer::RBC_MissleAttack(RBC_CPlayer* victim){
	victim->RBC_HurtHero(missle[0].RBC_GetDamage());
	victim->RBC_ChangeHeroStatus(0,7);
}

void RBC_CPlayer::RBC_SetHero(RBC_CHero *ahero){
	printf("Setting hero %s for player\n", ahero->RBC_GetName());
	hero=ahero;
	actualstate.state=0;
	actualstate.value=0;
}

void RBC_CPlayer::RBC_DrawHitboxes(void){
	std::vector<RBC_CHitbox> hb=hero->RBC_GetActualHitboxes(facedirection, actualstate.state, actualstate.value, framenumber);
	for(int i=0; i<hb.size(); i++){
		RBC_CEngineFunctions::RBC_DrawRect(hb[i].x+x+(facedirection?leftdifference:0), hb[i].y+y, hb[i].w, hb[i].h, hb[i].offensive?255:0, hb[i].defensive?255:0,hb[i].offensive||hb[i].defensive?0:255);
	}
}

std::vector<RBC_CHitbox> RBC_CPlayer::RBC_GetHitboxes(void){
	std::vector<RBC_CHitbox> hb=hero->RBC_GetActualHitboxes(facedirection, actualstate.state, actualstate.value, framenumber);
	for(int i=0; i<hb.size(); i++){
		hb[i].x+=(x+(facedirection?leftdifference:0));
		hb[i].y+=y;
	}
	return hb;
}

void RBC_CPlayer::RBC_AddStateToHistory(RBC_CPlayerState akey, bool pressed){

	if(keyhistory.size()>=20){
		keyhistory.erase(keyhistory.begin());
	}

	if(keyhistory.size()){
		int bf;
		RBC_CPlayerState sf;
		for(int i=0; i<keyhistory.size()-1; ++i){
			if(keyhistory[i].time>keyhistory[i+1].time){
				if(RBC_CKeyboard::RBC_KeyDown(keyhistory[i].key) &&
					RBC_CKeyboard::RBC_KeyDown(keyhistory[i+1].key)){

					if(keyhistory[i].start > keyhistory[i+1].start){
						bf=keyhistory[i].time;
						keyhistory[i].time=keyhistory[i+1].time;
						keyhistory[i+1].time=bf;
						sf=keyhistory[i];
						keyhistory[i]=keyhistory[i+1];
						keyhistory[i+1]=sf;
					}
				}else
				if(RBC_CKeyboard::RBC_KeyDown(keyhistory[i].key)){
				bf=keyhistory[i].time;
				keyhistory[i].time=keyhistory[i+1].time;
				keyhistory[i+1].time=bf;
				sf=keyhistory[i];
				keyhistory[i]=keyhistory[i+1];
				keyhistory[i+1]=sf;
				}
			}
		}

		if(pressed){
			keyhistory.push_back(akey);
			keyhistory[keyhistory.size()-1].time=RBC_CEngineFunctions::RBC_GetTicks()/100;
			keyhistory[keyhistory.size()-1].start=RBC_CEngineFunctions::RBC_GetTicks()/100;
		}else{
			for(int i=keyhistory.size()-1; i>=0; i--){
				if(keyhistory[i].key==akey.key){
					keyhistory[i].time=RBC_CEngineFunctions::RBC_GetTicks()/100;
					i=-1;
				}
			}
		}
	}else{
		keyhistory.push_back(akey);
		keyhistory[keyhistory.size()-1].time=RBC_CEngineFunctions::RBC_GetTicks()/100;
	}
}

void RBC_CPlayer::RBC_DrawHistory(void){
	RBC_CEngineFunctions::RBC_Write(5, 650, "P[0] history:");
	for(int i=0; i<keyhistory.size(); i++){
		RBC_CEngineFunctions::RBC_Write(5+i*50, 670, keyhistory[i].key);
		RBC_CEngineFunctions::RBC_Write(5+i*50, 700, keyhistory[i].time);
	}
}

void RBC_CPlayer::RBC_DrawMissles(void){
	for(int i=0; i<missle.size(); i++){
		RBC_CEngineFunctions::RBC_BlitSurface(missle[i].x, missle[i].y, missle[i].RBC_GetBitmap());
		if(facedirection){
			RBC_CEngineFunctions::RBC_DrawRect(missle[i].x+missle[i].RBC_ReturnWidth()+25, missle[i].y+20, 75, 3, 150, 150, 150);
			RBC_CEngineFunctions::RBC_DrawRect(missle[i].x+missle[i].RBC_ReturnWidth()+25, missle[i].y+80, 25, 3, 150, 150, 150);
			RBC_CEngineFunctions::RBC_DrawRect(missle[i].x+missle[i].RBC_ReturnWidth()+25, missle[i].y+140, 75, 3, 150, 150, 150);
		}else{
			RBC_CEngineFunctions::RBC_DrawRect(missle[i].x-100, missle[i].y+20, 75, 3, 150, 150, 150);
			RBC_CEngineFunctions::RBC_DrawRect(missle[i].x-50, missle[i].y+80, 25, 3, 150, 150, 150);
			RBC_CEngineFunctions::RBC_DrawRect(missle[i].x-100, missle[i].y+140, 75, 3, 150, 150, 150);
		}
	}
}

void RBC_CPlayer::RBC_DrawMisslesHitboxes(void){
	for(int i=0; i<missle.size(); i++){
		for(int j=0; j<missle[0].RBC_GetHitboxesNumber(); j++){
			RBC_CEngineFunctions::RBC_DrawRect(missle[i].RBC_GetHitboxes()[j].x, missle[i].RBC_GetHitboxes()[j].y, missle[i].RBC_GetHitboxes()[j].w, missle[i].RBC_GetHitboxes()[j].h,  255, 0, 0);
		}
	}
}

int RBC_CPlayer::RBC_GetStateKey(int s, int v){
	for(int i=0; i<statekey.size(); i++){
		if(statekey[i].state==s && statekey[i].value==v){return statekey[i].key;}
	}
	return 0;
}

void RBC_CPlayer::RBC_Refresh(bool blockkeyboard){
	for(int i=0; i<missle.size(); i++){
		if(facedirection){missle[i].RBC_MoveMissleLeft();}
		else{missle[i].RBC_MoveMissleRight();}
	}

	if(facedirection){leftdifference=hero->RBC_GetTheWidestBitmap()-hero->RBC_Draw(facedirection, actualstate.state, actualstate.value,framenumber)->w;}
	if(hero->RBC_GetFramesCount(actualstate.state, actualstate.value)>framenumber){
			if(actualstate.state==0){
				if(actualstate.value==1){x+=5;}
				else if(actualstate.value==2){if(x>5){x-=5;}}
				else if(actualstate.value==4){
						if(framenumber<hero->RBC_GetFramesCount(0,4)/2){y-=hero->RBC_GetFramesCount(0,4)-framenumber;}
						else if(framenumber>=hero->RBC_GetFramesCount(0,4)/2){y+=framenumber;}
				}
				else if(actualstate.value==6 && hero->RBC_GetActualFrameNumber(actualstate.state, actualstate.value, framenumber)==hero->RBC_GetMissle().RBC_GetStartFrame()){if(!thrown){RBC_PushBackMissle();thrown=1;}}else{thrown=0;}
			}
			else
			if(actualstate.state==3){
				if(actualstate.value==0){
					if(!facedirection){x++;}
					else{x--;}
				}else
				if(actualstate.value==1){
					if(!facedirection){x--;}
					else{x++;}
				}
			}
	framenumber++;

	}else{
		RBC_ChangeHeroStatus(0,0);
		if(!blockkeyboard){RBC_HandleKeyboard(); /**< DO NOT REMOVE- it's necessary to provide actions repeating*/}
		framenumber=0;
	}
}

void RBC_CPlayer::RBC_DestroyMissle(int x){
	if(x<missle.size()){
		missle.erase(missle.begin()+x, missle.begin()+x+1);
	}
}

void RBC_CPlayer::RBC_HandleKeyboard(void){
	for(int i=0; i<statekey.size(); i++){
		if(hero->RBC_GetActionRepeat(statekey[i].state, statekey[i].value)){
			if(RBC_CKeyboard::RBC_KeyPressed(statekey[i].key)){RBC_AddStateToHistory(statekey[i], 1);}
			if(RBC_CKeyboard::RBC_KeyDown(statekey[i].key)){
					RBC_AddStateToHistory(statekey[i], 0);
				if(hero->RBC_CheckSpecials(keyhistory)!=-1){
					RBC_ChangeHeroStatus(2, hero->RBC_CheckSpecials(keyhistory));
					//keyhistorytime[keyhistorytime.size()-1]*=10;
				}else
				if(hero->RBC_CheckComplexActions(keyhistory, facedirection)!=-1){
					//printf("FOUND\n");
					RBC_ChangeHeroStatus(3, hero->RBC_CheckComplexActions(keyhistory, facedirection));
					//keyhistorytime[keyhistorytime.size()-1]*=10;
				}
				else{

					RBC_ChangeHeroStatus(statekey[i].state, statekey[i].value);
				}
			}
		}else{
			if(RBC_CKeyboard::RBC_KeyPressed(statekey[i].key)){
				RBC_AddStateToHistory(statekey[i], 1);
				if(hero->RBC_CheckSpecials(keyhistory)!=-1){
					RBC_ChangeHeroStatus(2, hero->RBC_CheckSpecials(keyhistory));
					//keyhistorytime[keyhistorytime.size()-1]*=10;
				}else
				if(hero->RBC_CheckComplexActions(keyhistory, facedirection)!=-1){
					//printf("FOUND\n");
					RBC_ChangeHeroStatus(3, hero->RBC_CheckComplexActions(keyhistory, facedirection));
					//keyhistorytime[keyhistorytime.size()-1]*=10;
				}
				else{
					RBC_ChangeHeroStatus(statekey[i].state, statekey[i].value);
				}
			}
		}
	}
}

void RBC_CPlayer::RBC_FlipDirection(void){
	facedirection=!facedirection;
	//if(facedirection){x+=leftdifference;}else{x-=leftdifference;}
}
