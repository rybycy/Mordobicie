#include "RBC_CHeroBasicAttack.h"

RBC_CHeroBasicAttack::RBC_CHeroBasicAttack(const char *naem){
		printf("Creating basic attack %s", naem);
		multipier=2;
		repeat=0;
		knockdown=0;
		actionname=naem;
		tree="basic";
}

void RBC_CHeroBasicAttack::RBC_LoadHitboxes(const char *heroname){
	printf("Starting loading hitboxes procedure for %s\n", heroname);
	std::string path= "data/heroes/";
    path+=heroname;
    path+="/";
    path+=heroname;
    path+=".xml";
    std::string buffpath;

	knockdown=atoi(RBC_CXMLParser::RBC_GetXMLData("document", tree.c_str(), actionname.c_str(), "knockdown", 0));
	RBC_CXMLParser::RBC_LoadXMLFile(path.c_str());
	for(int i=0; i<LIMITER; i++){
		buffhitb.x=atoi(RBC_CXMLParser::RBC_GetXMLData("document", tree.c_str(), actionname.c_str(), "x", i));
		if(buffhitb.x==NULL){i=LIMITER+1;continue;}
		buffhitb.y=atoi(RBC_CXMLParser::RBC_GetXMLData("document", tree.c_str(), actionname.c_str(), "y", i));
		buffhitb.w=atoi(RBC_CXMLParser::RBC_GetXMLData("document", tree.c_str(), actionname.c_str(), "w", i));
		buffhitb.h=atoi(RBC_CXMLParser::RBC_GetXMLData("document", tree.c_str(), actionname.c_str(), "h", i));
		buffhitb.start=atoi(RBC_CXMLParser::RBC_GetXMLData("document", tree.c_str(), actionname.c_str(), "startframe", i));
		buffhitb.finish=atoi(RBC_CXMLParser::RBC_GetXMLData("document", tree.c_str(), actionname.c_str(), "finishframe", i));
		buffhitb.offensive=atoi(RBC_CXMLParser::RBC_GetXMLData("document", tree.c_str(), actionname.c_str(), "offensive", i)) ? 1:0;
		buffhitb.defensive=0;

		hitbox.push_back(buffhitb);
		printf("\tI've just finished loading hitbox for %s\n", actionname.c_str());
	}
	RBC_LoadAttribute(heroname, "multipier", &multipier);
	RBC_LoadAttribute(heroname, "repeat", &repeat);
	RBC_LoadAttribute(heroname, "length", &length);
	RBC_LoadAttribute(heroname, "damage", &damage);
	printf("Loading hitboxes finished\n\n");
}


