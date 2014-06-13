#include "RBC_CHeroSpecialAttack.h"

RBC_CHeroSpecialAttack::RBC_CHeroSpecialAttack(const char *naem){
	actionname=naem;
	tree="special";
}

bool RBC_CHeroSpecialAttack::RBC_IsSpecialAttackExecuted(std::vector<RBC_CPlayerState> states){
	if(combination.size()>states.size()){return 0;}
	else{
		for(int i=0; i<combination.size(); ++i){
			if(states[states.size()-combination.size()+i].state!=combination[i].state || states[states.size()-combination.size()+i].value!=combination[i].value){return 0;}
		}
		for(int i=0; i<combination.size()-1; ++i){
			if(abs(states[states.size()-combination.size()+i+1].time-states[states.size()-combination.size()+i].time)>2){return 0;}
		}
	}
	for(int i=0;i<combination.size(); ++i){
		states[states.size()-combination.size()+i].used=1;
	}
	return 1;
}

void RBC_CHeroSpecialAttack::RBC_PushBackHitbox(int x, int y, int w, int h, int start, int finish, bool offensive, bool defensive){
	RBC_CHitbox bufhb;

	bufhb.x=x;
	bufhb.y=y;
	bufhb.w=w;
	bufhb.h=h;
	bufhb.start=start;
	bufhb.finish=finish;
	bufhb.offensive=offensive;
	bufhb.defensive=defensive;
	hitbox.push_back(bufhb);
}
