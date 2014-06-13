#include "RBC_CHeroAction.h"

int RBC_CHeroAction::widestbitmap;

RBC_CHeroAction::RBC_CHeroAction(const char *naem){
	printf("Creating action %s", naem);
	multipier=2;
	length=0;
	actionname=naem;
	repeat=0;
	tree="action";
}

void RBC_CHeroAction::RBC_LoadHitboxes(const char *heroname){
	printf("Starting loading hitboxes procedure for %s\n", heroname);
	std::string path= "data/heroes/";
    path+=heroname;
    path+="/";
    path+=heroname;
    path+=".xml";
    std::string buffpath;
	RBC_CXMLParser::RBC_LoadXMLFile(path.c_str());
	for(int i=0; i<LIMITER; i++){
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
	RBC_LoadAttribute(heroname, "multipier", &multipier);
	RBC_LoadAttribute(heroname, "repeat", &repeat);
	RBC_LoadAttribute(heroname, "length", &length);
	printf("Loading hitboxes and attributes (mult- %i; rpt- %i; len- %i) finished\n", multipier, repeat,length);
}

void RBC_CHeroAction::RBC_LoadAttribute(const char *heroname, const char *attribute, int *dest){
	printf("Loading %s for %s...\n", attribute, actionname.c_str());
	for(int i=0; i<LIMITER; i++){
		if(RBC_CXMLParser::RBC_GetXMLValue("document", tree.c_str(), i)==NULL){i=LIMITER+1;continue;}
		else{
			stringbuff=RBC_CXMLParser::RBC_GetXMLValue("document", tree.c_str(), i);
			if(stringbuff==actionname){
				intbuff=atoi(RBC_CXMLParser::RBC_GetXMLData("document", tree.c_str(), attribute, i));
				if(intbuff){
					printf("\tLoading %s for %s -> %i\n", attribute, stringbuff.c_str(), intbuff);
					*dest=intbuff;
				}
			}
		}
	}
	printf("Loading %s finished\n\n", attribute);
}

void RBC_CHeroAction::RBC_LoadAttribute(const char *heroname, const char *attribute, bool *dest){
	printf("Loading %s for %s...\n", attribute, actionname.c_str());
	for(int i=0; i<LIMITER; i++){
		if(RBC_CXMLParser::RBC_GetXMLValue("document", tree.c_str(), i)==NULL){i=LIMITER+1;continue;}
		else{
			stringbuff=RBC_CXMLParser::RBC_GetXMLValue("document", tree.c_str(), i);
			if(stringbuff==actionname){
				intbuff=atoi(RBC_CXMLParser::RBC_GetXMLData("document", tree.c_str(), attribute, i));
				if(intbuff){
					printf("\tLoading %s for %s -> %i\n", attribute, stringbuff.c_str(), intbuff);
					*dest=intbuff;
				}
			}
		}
	}
	printf("Loading %s finished\n\n", attribute);
}

void RBC_CHeroAction::RBC_LoadBitmaps(const char *heroname){
	printf("Starting loading bitmaps procedure for %s\n", heroname);
	std::string path= "data/heroes/";
    path+=heroname;
    path+= "/graphics/";
    path+=actionname;
    path+="/";
    path+= heroname;
    std::string buffpath;
    for (int i=0; i<LIMITER; i++){
        buffpath=path;
        buffpath+=itoa(i, charbuff, 10);
        buffpath+=".png";
        if(RBC_CEngineFunctions::RBC_LoadIMG(buffpath.c_str())!=NULL){
			bitmap.push_back(RBC_CEngineFunctions::RBC_LoadIMG(buffpath.c_str()));
			if(bitmap[bitmap.size()-1]->w > widestbitmap){widestbitmap=bitmap[bitmap.size()-1]->w;}
			printf("\tLoading %s done\n", buffpath.c_str());
        }else{i=LIMITER+1;continue;}
    }
    printf("Bitmaps loading procedure finished\n\n");
}

void RBC_CHeroAction::RBC_ReverseActionAnimation(void){
	SDL_Surface* buffsurf;
	printf("Habaziaba\n");
	for(int i=0; i<bitmap.size()/2; i++){
		buffsurf=bitmap[bitmap.size()-1-i];
		bitmap[bitmap.size()-1-i]=bitmap[i];
		bitmap[i]=buffsurf;
	}
}

void RBC_CHeroAction::RBC_FlipActionAnimation(void){
	for(int i=0; i<bitmap.size(); i++){
		bitmap[i]=RBC_CEngineFunctions::RBC_FlipSurface(bitmap[i]);
	}
	for(int i=0; i<hitbox.size(); i++){
		hitbox[i].x=bitmap[hitbox[i].start]->w-(hitbox[i].x+hitbox[i].w);
	}
}

std::vector<RBC_CHitbox> RBC_CHeroAction::RBC_GetActualHitbox(int frame){
	std::vector<RBC_CHitbox> buff;
	for(int i=0; i<hitbox.size(); i++){
		if(hitbox[i].start <= frame/multipier && hitbox[i].finish >=frame/multipier){
			buff.push_back(hitbox[i]);
		}
	}
	return buff;
}
