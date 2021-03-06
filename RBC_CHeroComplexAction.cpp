#include "RBC_CHeroComplexAction.h"

RBC_CHeroComplexAction::RBC_CHeroComplexAction(const char *naem)
{
	actionname=naem;
	tree="complexaction";
}


bool RBC_CHeroComplexAction::RBC_IsComplexActionExecuted(std::vector<RBC_CPlayerState> states, bool facedirection){
	if(combination.size()>states.size()){return 0;}
	else{
		for(int i=0; i<combination.size(); ++i){
			if(facedirection && combination[i].state==0 && combination[i].value==1){
				if(states[states.size()-combination.size()+i].state!=0 || states[states.size()-combination.size()+i].value!=2){return 0;}
			}else
			if(facedirection && combination[i].state==0 && combination[i].value==2){
				if(states[states.size()-combination.size()+i].state!=0 || states[states.size()-combination.size()+i].value!=1){return 0;}
			}else{
				if(states[states.size()-combination.size()+i].state!=combination[i].state || states[states.size()-combination.size()+i].value!=combination[i].value){return 0;}
			}
			if(i<combination.size()-1){
				if(states[states.size()-combination.size()+i].time-states[states.size()-combination.size()+i+1].time){return 0;}
			}
		}
	}
	return 1;
}

void RBC_CHeroComplexAction::RBC_LoadHitboxes(const char *heroname){
	printf("Starting loading hitboxes procedure for %s\n", heroname);
	std::string path= "data/heroes/";
    path+=heroname;
    path+="/";
    path+=heroname;
    path+=".xml";
    std::string buffpath;
	RBC_CXMLParser::RBC_LoadXMLFile(path.c_str());
	printf("COMPLEX %s-%s\n", tree.c_str(), actionname.c_str());
	for(int i=0; i<LIMITER; i++){
		if(RBC_CXMLParser::RBC_GetXMLValue("document", tree.c_str(), actionname.c_str(), i)==NULL){i=LIMITER+1;continue;}
		if(RBC_CXMLParser::RBC_GetXMLValue("document", tree.c_str(), actionname.c_str(), i)[0]=='c'){
			printf("dodaje %i %i \n", atoi(RBC_CXMLParser::RBC_GetXMLData("document", tree.c_str(), actionname.c_str(), "state", i)), atoi(RBC_CXMLParser::RBC_GetXMLText("document", tree.c_str(), actionname.c_str(), i)));
			RBC_AddToCombination(atoi(RBC_CXMLParser::RBC_GetXMLData("document", tree.c_str(), actionname.c_str(), "state", i)), atoi(RBC_CXMLParser::RBC_GetXMLText("document", tree.c_str(), actionname.c_str(), i)));
		}
		if(RBC_CXMLParser::RBC_GetXMLValue("document", tree.c_str(), actionname.c_str(), i)[0]=='h'){
			buffhitb.x=atoi(RBC_CXMLParser::RBC_GetXMLData("document", tree.c_str(), actionname.c_str(), "x", i));
			if(buffhitb.x==NULL){i=LIMITER+1;continue;}
			buffhitb.y=atoi(RBC_CXMLParser::RBC_GetXMLData("document", tree.c_str(), actionname.c_str(), "y", i));
			buffhitb.w=atoi(RBC_CXMLParser::RBC_GetXMLData("document", tree.c_str(), actionname.c_str(), "w", i));
			buffhitb.h=atoi(RBC_CXMLParser::RBC_GetXMLData("document", tree.c_str(), actionname.c_str(), "h", i));
			buffhitb.start=atoi(RBC_CXMLParser::RBC_GetXMLData("document", tree.c_str(), actionname.c_str(), "startframe", i));
			buffhitb.finish=atoi(RBC_CXMLParser::RBC_GetXMLData("document", tree.c_str(), actionname.c_str(), "finishframe", i));
			buffhitb.defensive=atoi(RBC_CXMLParser::RBC_GetXMLData("document", tree.c_str(), actionname.c_str(), "defensive", i)) ? 1:0;
			buffhitb.offensive=0;
			hitbox.push_back(buffhitb);
			printf("\tI've just finished loading hitbox for %s\n", actionname.c_str());
		}
	}
	RBC_LoadAttribute(heroname, "multipier", &multipier);
	RBC_LoadAttribute(heroname, "repeat", &repeat);
	RBC_LoadAttribute(heroname, "length", &length);
	printf("Loading hitboxes finished\n\n");
}

void RBC_CHeroComplexAction::RBC_ReverseActionDirectionCombination(void){
	for(int i=0; i<combination.size(); i++){
		if(combination[i].state==0 && combination[i].value==1){combination[i].value=2;}
		else if(combination[i].state==0 && combination[i].value==2){combination[i].value=1;}
	}
}
