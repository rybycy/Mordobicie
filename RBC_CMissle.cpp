#include "RBC_CMissle.h"

void RBC_CMissle::RBC_LoadMissleXML(void){
	printf("Starting loading hitboxes procedure for missle\n");
	std::string path= "data/weapons/Missle";
    path+=itoa(number, charbuff, 10);
    path+=".xml";
    printf("LOADING from file %s\n", path.c_str());
    RBC_CHitbox buffhitb;
	RBC_CXMLParser::RBC_LoadXMLFile(path.c_str());
	damage=atoi(RBC_CXMLParser::RBC_GetXMLData("missle", "damage", 0));
	speed=atoi(RBC_CXMLParser::RBC_GetXMLData("missle", "speed", 0));
	height=atoi(RBC_CXMLParser::RBC_GetXMLData("missle", "height", 0));
	startframe=atoi(RBC_CXMLParser::RBC_GetXMLData("missle", "startframe", 0));
	for(int i=1; i<LIMITER; i++){
		buffhitb.x=atoi(RBC_CXMLParser::RBC_GetXMLData("missle", "x", i));
		if(buffhitb.x==NULL){i=LIMITER+1;continue;}
		buffhitb.y=atoi(RBC_CXMLParser::RBC_GetXMLData("missle", "y", i));
		buffhitb.w=atoi(RBC_CXMLParser::RBC_GetXMLData("missle", "w", i));
		buffhitb.h=atoi(RBC_CXMLParser::RBC_GetXMLData("missle", "h", i));
		buffhitb.defensive=0;
		buffhitb.offensive=1;
		hitbox.push_back(buffhitb);
		printf("\tI've just finished loading hitbox for missle: %i %i %i %i\n", buffhitb.x, buffhitb.y, buffhitb.w, buffhitb.h);
	}
	printf("Loading hitboxes finished\n\n");

}

void RBC_CMissle::RBC_LoadMissleBitmap(void){
	printf("Starting loading bitmap procedure for missle\n");
	std::string path= "data/weapons/Missle";
	path+=itoa(number, charbuff, 10);
	path+=".png";
	printf("FROM %s\n", path.c_str());
    //for (int i=0; i<LIMITER; i++){
        if(RBC_CEngineFunctions::RBC_LoadIMG(path.c_str())!=NULL){
			bitmap=RBC_CEngineFunctions::RBC_LoadIMG(path.c_str());
			printf("\tLoading missle %i done\n", number);
        }//else{i=LIMITER+1;continue;}
    //}
    printf("Bitmap loading procedure finished\n\n");
}
