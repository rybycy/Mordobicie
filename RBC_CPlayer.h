#ifndef RBC_CPlayer_h
#define RBC_CPlayer_h

#include <vector>


#include "RBC_CHero.h"
#include "RBC_CHitbox.h"
#include "RBC_CKeyboard.h"
#include "RBC_CPlayerState.h"

class RBC_CPlayer{
private:

    int x, y;		/**< Coordinates of player */
	int hppercent;
	bool facedirection; /**< 0- right 1- left */

	int framenumber; /**< The number of frame actually used in animation */
	RBC_CPlayerState actualstate; /**< Actual state of hero */
	int movementlength; /**< Actual movement length, made for comparing with action length */

	std::vector<RBC_CMissle> missle;

	int winctr;

	int lastmissle;
	int thrown;

	int leftdifference;

	RBC_CHero* hero; /**< Pointer SET ON NULL in the CPlayer constructor. There's necessity of setting it with SetHero function */

	std::vector<RBC_CPlayerState> statekey;
	std::vector<RBC_CPlayerState> keyhistory; /**< integers like in herostatis */

public:
	bool dealt;

	int RBC_GetHeroWidth(void){return hero->RBC_Draw(facedirection, actualstate.state, actualstate.value,framenumber)->w;}

	int RBC_GetX(void){return x+(facedirection?leftdifference:0);}

	int RBC_GetY(void){return y;}

	RBC_CPlayerState RBC_GetHeroStatus(void){return actualstate;}

	int RBC_GetHitpoints(void){return hppercent;}

	int RBC_GetHeroState(void){return actualstate.state;}

	int RBC_GetFrameNumber(void){return framenumber;}

	int RBC_GetWinCounter(void){return winctr;}

	int RBC_GetActualDamage(void){return hero->RBC_GetDamage(actualstate.state, actualstate.value);}

	std::vector<RBC_CHitbox> RBC_GetHitboxes(void);

	bool RBC_ReadyForAttack(void){return (!actualstate.state && actualstate.value!=4);} /**< Returns true if player is able to attack */

	bool RBC_GetActionRepeat(void){return hero->RBC_GetActionRepeat(actualstate.state, actualstate.value);} /**< Holding the key allows to loop action*/

	bool RBC_GetFaceDirection(void){return facedirection;}

	int RBC_GetLeftDifference(void){return leftdifference;}

	const char* RBC_GetActualActionName(void){return hero->RBC_GetActionName(actualstate.state, actualstate.value);}

	int RBC_GetStateKey(int s, int v);

	std::vector<RBC_CMissle> RBC_GetMissles(void){return missle;}

	bool RBC_IsReadyToThrow(void);


	RBC_CPlayer(); /**< Completely useless constructor. Sets hero to NULL */


	void RBC_SetX(int ax){x=ax;}

	void RBC_SetXplus(int a=0){if(!a){x++;}else{x+=a;}}

	void RBC_SetXminus(int a=0){if(!a){x--;}else{x-=a;}}

	void RBC_SetY(int ay){y=ay;}

	void RBC_SetDirection(bool dir){facedirection=dir;}

	void RBC_SetButton(int akey, int astate, int avalue);

	void RBC_SetHero(RBC_CHero *ahero); /**< This function assigns a hero to player */

	void RBC_SetHitpoints(int hp){hppercent=hp;}

	void RBC_ChangeHeroStatus(int astate, int avalue);

	void RBC_PushBackMissle(void);

	void RBC_Attack(RBC_CPlayer* victim);

	void RBC_MissleAttack(RBC_CPlayer* victim);

	void RBC_AddToWinCounter(void){++winctr;}

	void RBC_HurtHero(int v){hppercent-=v;}

	void RBC_AddStateToHistory(RBC_CPlayerState key, bool pressed);

	void RBC_HandleKeyboard(void);

	void RBC_LoadHeroResources(void){hero->RBC_LoadResources();}

    void RBC_Refresh(bool blockkeyboard); /**< Changes states of hero which are time-dependent only  */

	void RBC_DestroyMissle(int x);

	void RBC_DrawMissles(void);

	void RBC_DrawMisslesHitboxes(void);

	void RBC_DrawHistory(void);

    void RBC_DrawHero(void); /**< With Draw() function from RBC_CHero class it draws hero on the screen */

    void RBC_DrawHitboxes(void);

    void RBC_DrawHPBar(void);

    void RBC_FlipDirection(void);


};

#endif
