#ifndef RBC_CHero_H
#define RBC_CHero_H

#include "RBC_CEngineFunctions.h"
#include "RBC_CXMLParser.h"
#include "RBC_CHeroAction.h"
#include "RBC_CHeroComplexAction.h"
#include "RBC_CHeroBasicAttack.h"
#include "RBC_CHeroSpecialAttack.h"
#include "RBC_CMissle.h"

#include <vector>

class RBC_CHero{
private:


    std::string name; /** The string which  contains name of hero. It's used for loading sprites*/

	bool loadedresources; /**< Prevents unnecessary resources reloading */

    std::vector<RBC_CHeroAction> action; /**< Non-attack actions */
    std::vector<RBC_CHeroComplexAction> complexaction;
    std::vector<RBC_CHeroBasicAttack> basic; /**< Basic attacks */
    std::vector<RBC_CHeroSpecialAttack> special; /**< Special attacks defined in xml file */

    std::vector<RBC_CHeroAction> action_left;
    std::vector<RBC_CHeroComplexAction> complexaction_left;
    std::vector<RBC_CHeroBasicAttack> basic_left;
    std::vector<RBC_CHeroSpecialAttack> special_left;
	/**< @up three vectors of left-side animations, hitboxes */

	RBC_CMissle missle;

	/**< Buffer variables */
	char charbuff[100];
    int intbuff;
    int leftsidedifference;
    std::string stringbuff;

public:
	const char* RBC_GetName(void){return name.c_str();}

	int RBC_GetFramesCount(int state, int status);

    std::vector<RBC_CHitbox> RBC_GetActualHitboxes(bool faec, int state, int status, int framenumber);

	const char* RBC_GetActionName(int state, int value);

	bool RBC_GetActionRepeat(int a, int b);

	int RBC_GetDamage(int state, int status);

	int RBC_GetTheWidestBitmap(void){return leftsidedifference;}

	RBC_CMissle RBC_GetMissle(void){return missle;}

	int RBC_GetActualFrameNumber(int state, int status, int framenumber);


    RBC_CHero(const char* naem); /**< Constructor just for adding name and creating paths to graphics */


	void RBC_LoadResources(void); /**< Loads all of resources forming a hero */

	void RBC_LoadHeroSpecials(void); /**< TODO: Change to inner version in each RBC_CHeroSpecialAttack class object. Loads hero special attacks */

	void RBC_SetMissle(int x){missle.RBC_SetNumber(x);}

    int RBC_CheckSpecials(std::vector<RBC_CPlayerState> states); /**< Checks if special attacks are in key history */

    int RBC_CheckComplexActions(std::vector<RBC_CPlayerState> states, bool facedirection); /**< Checks if special attacks are in key history */

    SDL_Surface* RBC_Draw(bool faec, int state, int status, int framenumber); /**< Function returns a surface to draw */

};

#endif
