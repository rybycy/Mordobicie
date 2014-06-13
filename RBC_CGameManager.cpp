#include "RBC_CGameManager.h"

std::vector<RBC_CHero*> RBC_CGameManager::heroes;
RBC_CPlayer RBC_CGameManager::player[2];

RBC_CMap RBC_CGameManager::actualmap;
int RBC_CGameManager::actualmapnumber;

std::vector<SDL_Surface*> RBC_CGameManager::mapsthumbnails;
std::vector<SDL_Surface*> RBC_CGameManager::heroesthumbnails;

int RBC_CGameManager::collisiontype;
char RBC_CGameManager::charbuff[100];

bool RBC_CGameManager::p0locked;
bool RBC_CGameManager::p1locked;

bool RBC_CGameManager::debugview;

int RBC_CGameManager::p0choose;
int RBC_CGameManager::p1choose;

bool RBC_CGameManager::blockkeyboard;

int RBC_CGameManager::gamestate;
bool RBC_CGameManager::done;
int RBC_CGameManager::fightstart;

int RBC_CGameManager::hbhviewstate;

int RBC_CGameManager::intbuff;

int RBC_CGameManager::shift;

void RBC_CGameManager::RBC_RefreshAll(void){
	if(gamestate==1){
		if(!p0locked){
			if(RBC_CKeyboard::RBC_KeyPressed((SDLK_a))){p0choose--;p0choose<0?p0choose+=heroes.size():0;}
			if(RBC_CKeyboard::RBC_KeyPressed((SDLK_d))){p0choose++;p0choose%=heroes.size();}
			if(RBC_CKeyboard::RBC_KeyPressed(SDLK_RETURN)){p0locked=1;}
		}
		if(!p1locked){
			if(RBC_CKeyboard::RBC_KeyPressed((SDLK_LEFT))){p1choose--;p1choose<0?p1choose+=heroes.size():0;}
			if(RBC_CKeyboard::RBC_KeyPressed((SDLK_RIGHT))){p1choose++;p1choose%=heroes.size();}
			if(RBC_CKeyboard::RBC_KeyPressed(SDLK_BACKSPACE)){p1locked=1;}
		}
		if(p1locked && p0locked){
			gamestate=2;
			RBC_LoadMapsThumbnails();
			//RBC_PurgeHeroesThumbnails();
		}

	}
	if(gamestate==2){
		if(RBC_CKeyboard::RBC_KeyPressed(SDLK_LEFT)){actualmapnumber--;actualmapnumber<0?actualmapnumber+=mapsthumbnails.size():0;}
		if(RBC_CKeyboard::RBC_KeyPressed(SDLK_RIGHT)){actualmapnumber++;actualmapnumber%=mapsthumbnails.size();}
		if(RBC_CKeyboard::RBC_KeyPressed(SDLK_RETURN)){
			actualmap.RBC_SetNumber(actualmapnumber);
			shift=0;
			//shift=actualmap.RBC_GetMapWidth()/2;
			gamestate=3;
			RBC_PurgeMapsThumbnails();
		}
	}else
	if(gamestate==3){ /**< Loading resources before face punching */
		RBC_DrawAll();
		actualmap.RBC_LoadBitmap();
		RBC_InitPlayers(0, heroes[p0choose], 0);
		RBC_InitPlayers(1, heroes[p1choose], 1);
		gamestate=4;
		fightstart=RBC_CEngineFunctions::RBC_GetTicks();
		blockkeyboard=1;
	}
	if(gamestate==4){ /**< Face slapping */
		if(RBC_CEngineFunctions::RBC_GetTicks()-fightstart>4000){blockkeyboard=0;}

		if(!player[0].RBC_GetFaceDirection() && player[0].RBC_GetX()>player[1].RBC_GetX()){RBC_FlipPlayers();}
		else if(player[0].RBC_GetFaceDirection() && player[0].RBC_GetX()<player[1].RBC_GetX()){RBC_FlipPlayers();}
		intbuff=player[0].RBC_GetX()+2*shift;
		intbuff+=player[1].RBC_GetX();
		if(player[0].RBC_GetFaceDirection()){intbuff+=player[0].RBC_GetHeroWidth();}
		else{intbuff+=player[1].RBC_GetHeroWidth();}
		intbuff=intbuff/2;

		if(shift>=0){
			if(shift>0 && intbuff-shift<RBC_CEngineFunctions::RBC_GetScreenW()/2)
			{
				shift--;
				player[0].RBC_SetXplus();
				player[1].RBC_SetXplus();
			}
			if(intbuff-shift>512 && actualmap.RBC_GetMapWidth()>shift+RBC_CEngineFunctions::RBC_GetScreenW() && player[0].RBC_GetX() && player[1].RBC_GetX())
			{
				shift++;
				player[0].RBC_SetXminus();
				player[1].RBC_SetXminus();
			}
		}
		for(int i=0; i<player[0].RBC_GetMissles().size(); i++){
			if(player[0].RBC_GetMissles()[i].x<-100 || player[0].RBC_GetMissles()[i].x>RBC_CEngineFunctions::RBC_GetScreenW()+100){player[0].RBC_DestroyMissle(i);}
		}
		for(int i=0; i<player[1].RBC_GetMissles().size(); i++){
			if(player[1].RBC_GetMissles()[i].x<-100 || player[1].RBC_GetMissles()[i].x>RBC_CEngineFunctions::RBC_GetScreenW()+100){player[1].RBC_DestroyMissle(i);}
		}
			if(player[0].RBC_GetX() < 0 ){player[0].RBC_SetX(0);}
		if(player[1].RBC_GetX() < 0 ){player[1].RBC_SetX(0);}
		if(player[0].RBC_GetX() + player[0].RBC_GetHeroWidth() > RBC_CEngineFunctions::RBC_GetScreenW()){
			player[0].RBC_SetXminus((player[0].RBC_GetX() + player[0].RBC_GetHeroWidth())-RBC_CEngineFunctions::RBC_GetScreenW());
		}
		if(player[1].RBC_GetX() + player[1].RBC_GetHeroWidth() > RBC_CEngineFunctions::RBC_GetScreenW()){
			player[1].RBC_SetXminus((player[1].RBC_GetX() + player[1].RBC_GetHeroWidth())-RBC_CEngineFunctions::RBC_GetScreenW());
		}

		player[0].RBC_Refresh(blockkeyboard);
		player[1].RBC_Refresh(blockkeyboard);

		switch(RBC_GetCollisionType(&player[0], &player[1])){
			case 0:
				collisiontype=0;
				break;
			case 1: /**< Offensive - offensive */
				collisiontype=1;
				player[0].RBC_Attack(&player[1]);player[1].RBC_Attack(&player[0]);
				break;
			case 2: /**< Offensive- defensive */
				collisiontype=2;
				//player[1].RBC_SetX(player[1].RBC_GetFaceDirection()?(player[1].RBC_GetX()+10):(player[1].RBC_GetX()-10));
				break;
			case 3: /**< Offensive - neutral */
				collisiontype=3;
				player[0].RBC_Attack(&player[1]);
				break;
			case 4: /**< Defensive - offensive */
				collisiontype=4;
				break;
			case 5: /**< Defensive - defensive */
				collisiontype=5;
				player[0].RBC_SetX(player[0].RBC_GetFaceDirection()?player[0].RBC_GetX()+10:player[0].RBC_GetX()-10);player[1].RBC_SetX(player[1].RBC_GetFaceDirection()?player[1].RBC_GetX()+10:player[1].RBC_GetX()-10);
				break;
			case 6: /**< Defensive - neutral */
				collisiontype=6;
				break;
			case 7: /**< Neutral - offensive */
				collisiontype=7;
				player[1].RBC_Attack(&player[0]);
				break;
			case 8: /**< Neutral - defensive */
				collisiontype=8;
				break;
			case 9: /**< Each one neutral */
				collisiontype=9;
				player[0].RBC_GetFaceDirection()?player[0].RBC_SetXplus(30):player[0].RBC_SetXminus(30);player[1].RBC_GetFaceDirection()?player[1].RBC_SetXplus(30):player[1].RBC_SetXminus(30);
				break;
			case 10: /**< missle - offensive */
				collisiontype=10;
				player[0].RBC_MissleAttack(&player[1]);
				break;
			case 11: /**< missle - defensive */
				collisiontype=11;
				break;
			case 12: /**< missle - neutral */
				collisiontype=12;
				player[0].RBC_MissleAttack(&player[1]);
				break;
			case 13: /**< offensive - missle */
				collisiontype=13;
				player[1].RBC_MissleAttack(&player[0]);
				break;
			case 14: /**< defensive - missle */
				collisiontype=14;
				break;
			case 15:/**< neutral - missle */
				collisiontype=15;
				player[1].RBC_MissleAttack(&player[0]);
				break;
		}

		//if(player[0].RBC_GetHitpoints()<=0){player[1].RBC_AddToWinCounter();player[0].RBC_SetHitpoints(0);player[1].RBC_SetHitpoints(0);player[0].RBC_SetX(50); player[1].RBC_SetX(600);}
		//if(player[1].RBC_GetHitpoints()<=0){player[0].RBC_AddToWinCounter();player[0].RBC_SetHitpoints(0);player[1].RBC_SetHitpoints(0);player[0].RBC_SetX(50); player[1].RBC_SetX(600);}
		if(player[0].RBC_GetHitpoints()<=0 || player[1].RBC_GetHitpoints()<=0){
			gamestate=5;
			fightstart=RBC_CEngineFunctions::RBC_GetTicks();
		}

	}else
	if(gamestate==5){
		blockkeyboard=1;

		if(player[0].RBC_GetHitpoints()<=0){player[0].RBC_SetHitpoints(0);player[0].RBC_ChangeHeroStatus(0, 8);}
		if(player[1].RBC_GetHitpoints()<=0){player[1].RBC_SetHitpoints(0);player[1].RBC_ChangeHeroStatus(0, 8);}

		player[0].RBC_Refresh(1);
		player[1].RBC_Refresh(1);

		if(RBC_CEngineFunctions::RBC_GetTicks()-fightstart>4000){
		p0locked=0;
		p1locked=0;

		p0choose=0;
		p1choose=1;

		RBC_LoadHeroesThumbnails();
		blockkeyboard=0;
		gamestate=1;
		}
	}
}


void RBC_CGameManager::RBC_KeyboardHandler(void){
	RBC_CKeyboard::RBC_Refresh();

	if(RBC_CKeyboard::RBC_KeyDown(SDLK_ESCAPE)){done=1;}

	if(gamestate==4){
		if(RBC_CKeyboard::RBC_KeyPressed(SDLK_z)){
			hbhviewstate++;hbhviewstate%=4;
		}
		if(RBC_CKeyboard::RBC_KeyPressed(SDLK_x)){
			debugview=!debugview;
		}

		if(!blockkeyboard){
		player[0].RBC_HandleKeyboard();
		player[1].RBC_HandleKeyboard();
		}


	}
}

void RBC_CGameManager::RBC_DrawAll(void){
	RBC_CEngineFunctions::RBC_ClearScreen();
	if(gamestate==1){
		RBC_CEngineFunctions::RBC_Write(10, 10, "Choose your hero:");

		RBC_CEngineFunctions::RBC_DrawRect(198, 98, 104, 104, 255, 0, 0);
		RBC_CEngineFunctions::RBC_DrawRect(RBC_CEngineFunctions::RBC_GetScreenW()-302, 98, 104, 104, 0, 255, 0);
		RBC_CEngineFunctions::RBC_BlitSurface(200, 100, heroesthumbnails[p0choose]);
		RBC_CEngineFunctions::RBC_BlitSurface(RBC_CEngineFunctions::RBC_GetScreenW()-300, 100, heroesthumbnails[p1choose]);

		for(int i=0; i<heroes.size(); i++){
			RBC_CEngineFunctions::RBC_Write(20+i*120, 350, heroes[i]->RBC_GetName());
			RBC_CEngineFunctions::RBC_DrawRect(18+i*120, 398, 104, 104, p0choose==i?255:0, p1choose==i?255:0, 120);
			RBC_CEngineFunctions::RBC_BlitSurface(20+i*120, 400, heroesthumbnails[i]);
		}
	}else

	if(gamestate==2){
		RBC_CEngineFunctions::RBC_Write(10, 10, "Select stage:");
		for(int i=0; i<mapsthumbnails.size(); i++){
			RBC_CEngineFunctions::RBC_DrawRect(18+i*120, 398, 104, 104, actualmapnumber==i?255:0, 0, actualmapnumber==i?0:255);
			RBC_CEngineFunctions::RBC_BlitSurface(20+i*120, 400, mapsthumbnails[i]);
		}
	}else
	if(gamestate==3){
		RBC_CEngineFunctions::RBC_Write(10, 10, "Loading resources");
		RBC_CEngineFunctions::RBC_BlitSurface(500, 300, mapsthumbnails[actualmapnumber]);
		RBC_CEngineFunctions::RBC_BlitSurface(250, 200, heroesthumbnails[p0choose]);
		RBC_CEngineFunctions::RBC_BlitSurface(750, 200, heroesthumbnails[p1choose]);
	}else

	if(gamestate==4 || gamestate==5){

		actualmap.RBC_Draw(shift);

		if(hbhviewstate>1){
			player[0].RBC_DrawHitboxes();
			player[1].RBC_DrawHitboxes();
			player[0].RBC_DrawMisslesHitboxes();
			player[1].RBC_DrawMisslesHitboxes();
		}

		if(hbhviewstate==1 || hbhviewstate>2){
			player[0].RBC_DrawHero();
			player[1].RBC_DrawHero();
			player[0].RBC_DrawMissles();
			player[1].RBC_DrawMissles();
		}


		RBC_CEngineFunctions::RBC_BlitSurface(20, 20, heroesthumbnails[p0choose]);
		RBC_CEngineFunctions::RBC_Write(150, 50, heroes[p0choose]->RBC_GetName());

		RBC_CEngineFunctions::RBC_BlitSurface(RBC_CEngineFunctions::RBC_GetScreenW()-120, 20, heroesthumbnails[p1choose]);
		RBC_CEngineFunctions::RBC_Write(RBC_CEngineFunctions::RBC_GetScreenW()-440, 50, heroes[p1choose]->RBC_GetName());


		RBC_CEngineFunctions::RBC_DrawRect(140, 20, 300, 30, 0, 150, 150);
		RBC_CEngineFunctions::RBC_DrawRect(140, 20, player[0].RBC_GetHitpoints()*3, 30,172,214,191);

		RBC_CEngineFunctions::RBC_DrawRect(RBC_CEngineFunctions::RBC_GetScreenW()-440, 20, 300, 30, 0, 150, 150);
		RBC_CEngineFunctions::RBC_DrawRect(RBC_CEngineFunctions::RBC_GetScreenW()-440+(300-player[1].RBC_GetHitpoints()*3), 20, player[1].RBC_GetHitpoints()*3, 30, 172,214,191);

		{
		if(debugview){/**< Debug view */
		RBC_CEngineFunctions::RBC_Write(880, 2, "FPS:");
		RBC_CEngineFunctions::RBC_Write(975, 2, RBC_CEngineFunctions::RBC_GetFPS());


		RBC_CEngineFunctions::RBC_Write(10, 120, "P[0] HP:");
		RBC_CEngineFunctions::RBC_Write(115, 120, player[0].RBC_GetHitpoints());
		RBC_CEngineFunctions::RBC_Write(10, 150, "P[0] X:");
		RBC_CEngineFunctions::RBC_Write(115, 150, player[0].RBC_GetX());
		RBC_CEngineFunctions::RBC_Write(10, 180, "P[0] Y:");
		RBC_CEngineFunctions::RBC_Write(115, 180, player[0].RBC_GetY());
		RBC_CEngineFunctions::RBC_Write(10, 210, "P[0] State:");
		RBC_CEngineFunctions::RBC_Write(115, 210, player[0].RBC_GetHeroState());
		RBC_CEngineFunctions::RBC_Write(10, 240, "P[0] Value:");
		RBC_CEngineFunctions::RBC_Write(115, 240, player[0].RBC_GetHeroStatus().value);
		RBC_CEngineFunctions::RBC_Write(10, 270, "P[0] Face:");
		RBC_CEngineFunctions::RBC_Write(115, 270, player[0].RBC_GetFaceDirection());
		RBC_CEngineFunctions::RBC_Write(10, 300, "P[0] ActNa:");
		RBC_CEngineFunctions::RBC_Write(115, 300, player[0].RBC_GetActualActionName());
		RBC_CEngineFunctions::RBC_Write(10, 330, "P[0] Wins:");
		RBC_CEngineFunctions::RBC_Write(115, 330, player[0].RBC_GetWinCounter());
		RBC_CEngineFunctions::RBC_Write(10, 360, "P[0] Misls:");
		RBC_CEngineFunctions::RBC_Write(115, 360, player[0].RBC_GetMissles().size());
		RBC_CEngineFunctions::RBC_Write(10, 390, "P[0] frame:");
		RBC_CEngineFunctions::RBC_Write(115, 390, player[0].RBC_GetFrameNumber());



		RBC_CEngineFunctions::RBC_Write(800, 120, "P[1] HP:");
		RBC_CEngineFunctions::RBC_Write(905, 120, player[1].RBC_GetHitpoints());
		RBC_CEngineFunctions::RBC_Write(800, 150, "P[1] X:");
		RBC_CEngineFunctions::RBC_Write(905, 150, player[1].RBC_GetX());
		RBC_CEngineFunctions::RBC_Write(800, 180, "P[1] Y:");
		RBC_CEngineFunctions::RBC_Write(905, 180, player[1].RBC_GetY());
		RBC_CEngineFunctions::RBC_Write(800, 210, "P[1] State:");
		RBC_CEngineFunctions::RBC_Write(905, 210, player[1].RBC_GetHeroState());
		RBC_CEngineFunctions::RBC_Write(800, 240, "P[1] Value:");
		RBC_CEngineFunctions::RBC_Write(905, 240, player[1].RBC_GetHeroStatus().value);
		RBC_CEngineFunctions::RBC_Write(800, 270, "P[1] Face:");
		RBC_CEngineFunctions::RBC_Write(905, 270, player[1].RBC_GetFaceDirection());
		RBC_CEngineFunctions::RBC_Write(800, 300, "P[1] ActNa:");
		RBC_CEngineFunctions::RBC_Write(905, 300, player[1].RBC_GetActualActionName());
		RBC_CEngineFunctions::RBC_Write(800, 330, "P[1] Wins:");
		RBC_CEngineFunctions::RBC_Write(905, 330, player[1].RBC_GetWinCounter());
		RBC_CEngineFunctions::RBC_Write(800, 360, "P[1] Misls:");
		RBC_CEngineFunctions::RBC_Write(905, 360, player[1].RBC_GetMissles().size());


		RBC_CEngineFunctions::RBC_Write(450, 10, "Collision:");
		RBC_CEngineFunctions::RBC_Write(545, 10, collisiontype);
		RBC_CEngineFunctions::RBC_Write(450, 40, "Middle:");
		RBC_CEngineFunctions::RBC_Write(545, 40, intbuff-shift);
		RBC_CEngineFunctions::RBC_Write(450, 70, "Shift:");
		RBC_CEngineFunctions::RBC_Write(545, 70, shift);
		player[0].RBC_DrawHistory();
		}
		if(gamestate==5)
		{
			player[0].RBC_GetHitpoints()?
				RBC_CEngineFunctions::RBC_Write(RBC_CEngineFunctions::RBC_GetScreenW()/2, RBC_CEngineFunctions::RBC_GetScreenH()/2, "Plejer 0 wins!"):
				RBC_CEngineFunctions::RBC_Write(RBC_CEngineFunctions::RBC_GetScreenW()/2, RBC_CEngineFunctions::RBC_GetScreenH()/2, "Plejer 1 wins!");
		}
		}
	}

	if(gamestate==4 && blockkeyboard && RBC_CEngineFunctions::RBC_GetTicks()-fightstart<4000){RBC_CEngineFunctions::RBC_Write(RBC_CEngineFunctions::RBC_GetScreenW()/2, RBC_CEngineFunctions::RBC_GetScreenH()/2, 3-(RBC_CEngineFunctions::RBC_GetTicks()-fightstart)/1000);}

	RBC_CEngineFunctions::RBC_Flip();
}

void RBC_CGameManager::RBC_MainLoop(void){
	hbhviewstate=1;
	debugview=1;
	RBC_InitHeroes();

	RBC_LoadHeroesThumbnails();

	RBC_BindButtons();

	player[1].RBC_SetX(600);
	gamestate=1;

	//temporarily set to fight stage

	while(!done){
	RBC_CEngineFunctions::RBC_NextLoop();

	RBC_RefreshAll();

	if(!blockkeyboard){RBC_KeyboardHandler();}

	RBC_DrawAll();
	}
}

void RBC_CGameManager::RBC_InitHeroes(void){
	if(!RBC_CXMLParser::RBC_LoadXMLFile("data/heroes/heroeslist.xml")){printf("Cannot load file data/heroes/heroeslist.xml\n");};
	std::string name;
	for(int i=0; i<1001; i++){
		printf("Requesting new hero...\n");
		if(RBC_CXMLParser::RBC_GetXMLData("heroeslist", "name", i)!=NULL){
			name=RBC_CXMLParser::RBC_GetXMLData("heroeslist", "name", i);
			heroes.push_back(new RBC_CHero(name.c_str()));
			heroes[heroes.size()-1]->RBC_SetMissle(atoi(RBC_CXMLParser::RBC_GetXMLData("heroeslist", "missle", i)));
			printf("Hero loaded\n");
		}else{printf("Nothing found, exiting\n");i=1002;continue;}
	}
}

void RBC_CGameManager::RBC_LoadMap(int number){
	actualmap.RBC_LoadBitmap();
}

void RBC_CGameManager::RBC_InitPlayers(int playernumber, RBC_CHero* hero, bool dir){
	player[playernumber].RBC_SetHero(hero);
	player[playernumber].RBC_LoadHeroResources();
	player[playernumber].RBC_SetDirection(dir);
}

int RBC_CGameManager::RBC_GetCollisionType(RBC_CPlayer* a, RBC_CPlayer* b){
	std::vector<RBC_CHitbox> recta=a->RBC_GetHitboxes();
	std::vector<RBC_CHitbox> rectb=b->RBC_GetHitboxes();

	for(int i=0; i<recta.size(); i++){
		for(int j=0; j<rectb.size(); j++){
			if(RBC_CheckCollision(recta[i], rectb[j])){
				printf("Collision detected: %i %i %i %i (%i %i) | %i %i %i %i (%i %i) | %i, %i, %i, %i\n", recta[i].x, recta[i].y, recta[i].w, recta[i].h, recta[i].offensive, recta[i].defensive, rectb[j].x, rectb[j].y, rectb[j].w, rectb[j].h, rectb[j].offensive, rectb[j].defensive, a->RBC_GetX(), a->RBC_GetY(), b->RBC_GetX(), b->RBC_GetY());
				if(recta[i].offensive){
					if(rectb[j].offensive){return 1;}else
					if(rectb[j].defensive){return 2;}
					else{return 3;}
				}else
				if(recta[i].defensive){
					if(rectb[j].offensive){return 4;}else
					if(rectb[j].defensive){return 5;}
					else{return 6;}
				}else{
					if(rectb[j].offensive){return 7;}else
					if(rectb[j].defensive){return 8;}
					else{return 9;}
				}
			}
		}
	}
	for(int i=0; i<a->RBC_GetMissles().size(); i++){
		for(int j=0; j<rectb.size(); j++){
			for(int k=0; k<a->RBC_GetMissles()[i].RBC_GetHitboxes().size(); k++){
				if(RBC_CheckCollision(a->RBC_GetMissles()[i].RBC_GetHitboxes()[k], rectb[j])){
					a->RBC_DestroyMissle(i);
					if(rectb[j].offensive){return 10;}else
					if(rectb[j].defensive){return 11;}
					else{return 12;}
				}else{
				}
			}
		}
	}

	for(int i=0; i<b->RBC_GetMissles().size(); i++){
		for(int j=0; j<recta.size(); j++){
			for(int k=0; k<b->RBC_GetMissles()[i].RBC_GetHitboxes().size(); k++){
				if(RBC_CheckCollision(b->RBC_GetMissles()[i].RBC_GetHitboxes()[k], recta[j])){
					b->RBC_DestroyMissle(i);
					if(recta[j].offensive){return 13;}else
					if(recta[j].defensive){return 14;}
					else{return 15;}
				}
			}
		}
	}

	for(int i=0; i<a->RBC_GetMissles().size(); i++){
		for(int j=0; j<b->RBC_GetMissles().size(); j++){
			for(int k=0; k<a->RBC_GetMissles()[i].RBC_GetHitboxes().size(); k++){
				for(int m=0; m<b->RBC_GetMissles()[i].RBC_GetHitboxes().size(); m++){
					if(RBC_CheckCollision(a->RBC_GetMissles()[i].RBC_GetHitboxes()[k], b->RBC_GetMissles()[j].RBC_GetHitboxes()[m])){
						a->RBC_DestroyMissle(i);
						b->RBC_DestroyMissle(j);
						return 16;
					}
				}
			}
		}
	}
return 0;
}

bool RBC_CGameManager::RBC_CheckCollision(RBC_CHitbox recta, RBC_CHitbox rectb){
	if(recta.x<=rectb.x && recta.y<=rectb.y && recta.x+recta.w>= rectb.x && recta.y+recta.h >= rectb.y){return 1;}
	if(recta.x<=rectb.x && recta.y>=rectb.y && recta.x+recta.w >= rectb.x && recta.y <=rectb.y+rectb.h){return 1;}
	if(recta.x>=rectb.x && recta.x<=rectb.x+rectb.w && recta.y>=rectb.y && recta.y<=rectb.y+rectb.h){return 1;}
	if(recta.x>=rectb.x && recta.x<=rectb.x+rectb.w && recta.y<=rectb.y && recta.y+recta.h>=rectb.y){return 1;}
return 0;
}



void RBC_CGameManager::RBC_BindButtons(void){


	std::string buffer;
	int x,y ;
	RBC_CXMLParser::RBC_LoadXMLFile("data/config.xml");

	for(int i=0; i<LIMITER; i++){
		if(RBC_CXMLParser::RBC_GetXMLData("options", "keybinding", "number", i)==NULL){i=LIMITER+1; continue;}
		x=atoi(RBC_CXMLParser::RBC_GetXMLData("options", "keybinding", "number", i));
		printf("Found key bindings for player[%i] \n", x);

		for(int j=0; j<LIMITER; j++){
				if(RBC_CXMLParser::RBC_GetXMLKey("options", "keybinding", j)!=NULL){
					buffer=RBC_CXMLParser::RBC_GetXMLKey("options", "keybinding", j);
					if(RBC_CXMLParser::RBC_GetXMLText("options", "keybinding", j)==NULL){printf("Config seems to be broken\n");i=LIMITER+1; j=LIMITER+1; continue;}
					y=atoi(RBC_CXMLParser::RBC_GetXMLText("options", "keybinding", i, j));
					printf("\tLoading KEY_%s for player %i on key %i...\n", buffer.c_str(), x, y);
					if(buffer=="RIGHT"){player[x].RBC_SetButton(y, 0, 1);}else
					if(buffer=="LEFT"){player[x].RBC_SetButton(y, 0, 2);}else
					if(buffer=="KNEEL"){player[x].RBC_SetButton(y, 0, 3);}else
					if(buffer=="JUMP"){player[x].RBC_SetButton(y, 0, 4);}else
					if(buffer=="HEAVYPUNCH"){player[x].RBC_SetButton(y, 1, 0);}else
					if(buffer=="HEAVYKICK"){player[x].RBC_SetButton(y, 1, 1);}else
					if(buffer=="MEDIUMPUNCH"){player[x].RBC_SetButton(y, 1, 2);}else
					if(buffer=="MEDIUMKICK"){player[x].RBC_SetButton(y, 1, 3);}else
					if(buffer=="LIGHTPUNCH"){player[x].RBC_SetButton(y, 1, 4);}else
					if(buffer=="LIGHTKICK"){player[x].RBC_SetButton(y, 1, 5);}else
					if(buffer=="BLOCK"){player[x].RBC_SetButton(y, 0, 5);}else
					if(buffer=="THROW"){player[x].RBC_SetButton(y, 0, 6);}
				}else{j=LIMITER+1;continue;}
		}
	}
}

void RBC_CGameManager::RBC_FlipPlayers(void){
	player[0].RBC_FlipDirection();
	player[1].RBC_FlipDirection();
}

void RBC_CGameManager::RBC_LoadMapsThumbnails(void){
	std::string path;
	for(int i=0; i<1001; i++){
		path="data/thumbnails/maps/Map";
		path+=itoa(i, charbuff, 10);
		path+=".png";
		mapsthumbnails.push_back(RBC_CEngineFunctions::RBC_LoadIMG(path.c_str()));
		if(mapsthumbnails[i]==NULL){mapsthumbnails.pop_back();i=1002;}
		printf("Thumbnail from path %s loaded successfully\n", path.c_str());
	}
}

void RBC_CGameManager::RBC_LoadHeroesThumbnails(void){
	std::string path;
	for(int i=0; i<heroes.size(); i++){
		path="data/thumbnails/heroes/";
		path+=heroes[i]->RBC_GetName();
		path+=".png";
		heroesthumbnails.push_back(RBC_CEngineFunctions::RBC_LoadIMG(path.c_str()));
		if(heroesthumbnails[i]==NULL){mapsthumbnails.pop_back();i=1002;}
		printf("Thumbnail from path %s loaded successfully\n", path.c_str());
	}
}

void RBC_CGameManager::RBC_PurgeMapsThumbnails(void){
	mapsthumbnails.clear();
}

void RBC_CGameManager::RBC_PurgeHeroesThumbnails(void){
	heroesthumbnails.clear();
}
