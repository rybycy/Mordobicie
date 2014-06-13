#include "RBC_CHero.h"

RBC_CHero::RBC_CHero(const char *naem){
	printf("Class CHero has received name of hero:'%s'\n", naem);
	name=naem;
	leftsidedifference=0;

	action.push_back("standing"); //0
	action.push_back("walking");  //1
	action.push_back("walking");  //2
	action.push_back("kneeling"); //3
	action.push_back("jumping");  //4
	action.push_back("block");    //5
	action.push_back("throwing"); //6
	action.push_back("hit");      //7
	action.push_back("knockdown"); //8

	complexaction.push_back("crouching");
	complexaction.push_back("crouching");

	basic.push_back("heavypunch"); //0
	basic.push_back("heavykick");  //1
	basic.push_back("mediumpunch");//2
	basic.push_back("mediumkick"); //3
	basic.push_back("lightpunch"); //4
	basic.push_back("lightkick");  //5

	loadedresources=0;
}

void RBC_CHero::RBC_LoadResources(void){
		if(!loadedresources){
			printf("Loading hero resources\n");
			int time=SDL_GetTicks();
			for(int i=0; i<action.size(); i++){
				action[i].RBC_LoadBitmaps(name.c_str());
				action[i].RBC_LoadHitboxes(name.c_str());
				action_left.push_back(action[i]);
				action_left[i].RBC_FlipActionAnimation();
			}
			leftsidedifference=action[0].RBC_GetTheWidestBitmap();
			action[2].RBC_ReverseActionAnimation();
			action_left[1].RBC_ReverseActionAnimation();

			for(int i=0; i<complexaction.size(); i++){
				complexaction[i].RBC_LoadBitmaps(name.c_str());
				complexaction[i].RBC_LoadHitboxes(name.c_str());
				complexaction_left.push_back(complexaction[i]);
				complexaction_left[i].RBC_FlipActionAnimation();
			}
			if(complexaction[0].RBC_GetTheWidestBitmap()>leftsidedifference){leftsidedifference=complexaction[0].RBC_GetTheWidestBitmap();}
			complexaction[1].RBC_ReverseActionAnimation();
			complexaction[1].RBC_ReverseActionDirectionCombination();

			for(int i=0; i<basic.size(); i++){
				basic[i].RBC_LoadBitmaps(name.c_str());
				basic[i].RBC_LoadHitboxes(name.c_str());
				basic_left.push_back(basic[i]);
				basic_left[i].RBC_FlipActionAnimation();
			}
			if(basic[0].RBC_GetTheWidestBitmap()>leftsidedifference){leftsidedifference=basic[0].RBC_GetTheWidestBitmap();}

			RBC_LoadHeroSpecials();
			for(int i=0; i<special.size(); i++){
				special[i].RBC_LoadBitmaps(name.c_str());
				special[i].RBC_LoadHitboxes(name.c_str());
				special_left.push_back(special[i]);
				special_left[i].RBC_FlipActionAnimation();
			}
			if(special[0].RBC_GetTheWidestBitmap()>leftsidedifference){leftsidedifference=special[0].RBC_GetTheWidestBitmap();}

			missle.RBC_LoadMissleBitmap();
			missle.RBC_LoadMissleXML();

			printf("Hero resources loading done in %i\n", SDL_GetTicks()-time);
			loadedresources=1;
		}else{printf("Resources for this hero has been already loaded, skipping\n");}
}

void RBC_CHero::RBC_LoadHeroSpecials(void){
	std::string stringbuff;
	printf("loading special hits for %s\n", name.c_str());
	for(int i=0; i<LIMITER; i++){
		if(RBC_CXMLParser::RBC_GetXMLValue("document", "special", i)==NULL){i=LIMITER+1;continue;}
		else{
			if(RBC_CXMLParser::RBC_GetXMLValue("document", "special", i)!=NULL){
				printf("DANA: %s\n", RBC_CXMLParser::RBC_GetXMLValue("document", "special", i));
				stringbuff=RBC_CXMLParser::RBC_GetXMLValue("document", "special", i);
				special.push_back(stringbuff.c_str());
				special[special.size()-1].RBC_SetDamage(atoi(RBC_CXMLParser::RBC_GetXMLData("document", "special", "damage", i)));
				special[special.size()-1].RBC_SetMultipier(atoi(RBC_CXMLParser::RBC_GetXMLData("document", "special", "multipier", i)));
				for(int j=0; j<LIMITER; j++){
					if(RBC_CXMLParser::RBC_GetXMLValue("document", "special", stringbuff.c_str(), j)==NULL){j=LIMITER+1;continue;}
					if(RBC_CXMLParser::RBC_GetXMLValue("document", "special", stringbuff.c_str(), j)[0]=='c'){
						special[special.size()-1].RBC_AddToCombination(atoi(RBC_CXMLParser::RBC_GetXMLData("document", "special", stringbuff.c_str(), "state", j)), atoi(RBC_CXMLParser::RBC_GetXMLText("document", "special", stringbuff.c_str(), j)));
					}else if(RBC_CXMLParser::RBC_GetXMLValue("document", "special", stringbuff.c_str(), j)[0]=='h'){
						special[special.size()-1].RBC_PushBackHitbox(
							atoi(RBC_CXMLParser::RBC_GetXMLData("document", "special", stringbuff.c_str(), "x", j)),
							atoi(RBC_CXMLParser::RBC_GetXMLData("document", "special", stringbuff.c_str(), "y", j)),
							atoi(RBC_CXMLParser::RBC_GetXMLData("document", "special", stringbuff.c_str(), "w", j)),
							atoi(RBC_CXMLParser::RBC_GetXMLData("document", "special", stringbuff.c_str(), "h", j)),
							atoi(RBC_CXMLParser::RBC_GetXMLData("document", "special", stringbuff.c_str(), "startframe", j)),
							atoi(RBC_CXMLParser::RBC_GetXMLData("document", "special", stringbuff.c_str(), "finishframe", j)),
							atoi(RBC_CXMLParser::RBC_GetXMLData("document", "special", stringbuff.c_str(), "offensive", j)),
							atoi(RBC_CXMLParser::RBC_GetXMLData("document", "special", stringbuff.c_str(), "defensive", j))
																		);
					}
				}
			}
		}
	}
}

const char* RBC_CHero::RBC_GetActionName(int state, int value){
	switch(state){
		case 0: return action[value].RBC_GetActionName();break;
		case 1: return basic[value].RBC_GetActionName();break;
		case 2: return special[value].RBC_GetActionName();break;
		case 3: return complexaction[value].RBC_GetActionName();break;
	}

	return NULL;
}

int RBC_CHero::RBC_GetFramesCount(int state, int status){ /**< TODO: insert all values to frames count */
	switch(state){
		case 0: return action[status].RBC_GetSize()*action[status].RBC_GetMultipier()-1;break;
		case 1: return basic[status].RBC_GetSize()*basic[status].RBC_GetMultipier()-1;break;
		case 2: return special[status].RBC_GetSize()*special[status].RBC_GetMultipier()-1;break;
		case 3: return complexaction[status].RBC_GetSize()*complexaction[status].RBC_GetMultipier()-1;break;
	}
	return 0;
}

int RBC_CHero::RBC_GetDamage(int state, int status){
	switch(state){
		case 1: return basic[status].RBC_GetDamage();break;
		case 2: return special[status].RBC_GetDamage();break;
	}
	return 0;
}

int RBC_CHero::RBC_GetActualFrameNumber(int state, int status, int framenumber){
		switch(state){
			case 0: return framenumber/action[status].RBC_GetMultipier();break;
			case 1: return framenumber/basic[status].RBC_GetMultipier();break;
			case 2: return framenumber/special[status].RBC_GetMultipier();break;
			case 3: return framenumber/complexaction[status].RBC_GetMultipier();break;
		}
}

SDL_Surface* RBC_CHero::RBC_Draw(bool faec, int state, int status, int framenumber){
    switch(faec){
			case 0:
				switch(state){
					case 0: return action[status].RBC_GetActualBitmap(framenumber/action[status].RBC_GetMultipier());break;
					case 1: return basic[status].RBC_GetActualBitmap(framenumber/basic[status].RBC_GetMultipier());break;
					case 2: return special[status].RBC_GetActualBitmap(framenumber/special[status].RBC_GetMultipier());break;
					case 3: return complexaction[status].RBC_GetActualBitmap(framenumber/complexaction[status].RBC_GetMultipier());break;
				}break;
			case 1:
				switch(state){
					case 0: return action_left[status].RBC_GetActualBitmap(framenumber/action_left[status].RBC_GetMultipier());break;
					case 1: return basic_left[status].RBC_GetActualBitmap(framenumber/basic_left[status].RBC_GetMultipier());break;
					case 2: return special_left[status].RBC_GetActualBitmap(framenumber/special_left[status].RBC_GetMultipier());break;
					case 3: return complexaction_left[status].RBC_GetActualBitmap(framenumber/complexaction_left[status].RBC_GetMultipier());break;
				}break;
	}
}

std::vector<RBC_CHitbox> RBC_CHero::RBC_GetActualHitboxes(bool faec, int state, int status, int framenumber){
	switch(faec){
			case 0:
				switch(state){
					case 0: return action[status].RBC_GetActualHitbox(framenumber%RBC_GetFramesCount(state, status));break;
					case 1: return basic[status].RBC_GetActualHitbox(framenumber%RBC_GetFramesCount(state, status));break;
					case 2: return special[status].RBC_GetActualHitbox(framenumber%RBC_GetFramesCount(state, status));break;
					case 3: return complexaction[status].RBC_GetActualHitbox(framenumber%RBC_GetFramesCount(state, status));break;
				}
			case 1:
				switch(state){
					case 0: return action_left[status].RBC_GetActualHitbox(framenumber%RBC_GetFramesCount(state, status));break;
					case 1: return basic_left[status].RBC_GetActualHitbox(framenumber%RBC_GetFramesCount(state, status));break;
					case 2: return special_left[status].RBC_GetActualHitbox(framenumber%RBC_GetFramesCount(state, status));break;
					case 3: return complexaction[status].RBC_GetActualHitbox(framenumber%RBC_GetFramesCount(state, status));break;
				}
	}
}

int RBC_CHero::RBC_CheckSpecials(std::vector<RBC_CPlayerState> states){
	for(int i=0;i<special.size();i++)
	{
		if(special[i].RBC_IsSpecialAttackExecuted(states)){return i;}
	}
	return -1;
}

int RBC_CHero::RBC_CheckComplexActions(std::vector<RBC_CPlayerState> states, bool facedirection){
	for(int i=0;i<complexaction.size();i++)
	{
		if(complexaction[i].RBC_IsComplexActionExecuted(states, facedirection)){return i;}
	}
	return -1;
}

bool RBC_CHero::RBC_GetActionRepeat(int a, int b){
	switch(a){
		case 0: return action[b].RBC_GetRepeat();break;
		case 1: return basic[b].RBC_GetRepeat();break;
		case 2: return special[b].RBC_GetRepeat();break;
		case 3: return complexaction[b].RBC_GetRepeat();break;
	}
	return 0;
}


