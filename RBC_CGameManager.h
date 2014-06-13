#ifndef RBC_CGAMEMANAGER_H
#define RBC_CGAMEMANAGER_H

#include <vector>
#include "RBC_CEngineFunctions.h"
#include "RBC_CPlayer.h"
#include "RBC_CKeyboard.h"
#include "RBC_CMap.h"


class RBC_CGameManager
{
	private:
		static std::vector<RBC_CHero*> heroes; /**< For initialization of heroes */
		static std::vector<SDL_Surface*> heroesthumbnails;

		static RBC_CMap actualmap;
		static std::vector<SDL_Surface*> mapsthumbnails;

		static int actualmapnumber;

		static RBC_CPlayer player[2]; /**< TODO: Should be changed to vector of players, temporarily only available */

		static int gamestate; /**< 0- intro 1- main menu 2- hero select menu 3- fight stage */
		static bool done; /**< Exit if done==1 */

		static int collisiontype;

		static char charbuff[100];

		static bool p0locked;

		static bool p1locked;

		static int p0choose;

		static int p1choose;

		static int intbuff;

		static bool blockkeyboard;

		static int fightstart;

		static bool debugview;

		static int shift;

		static int hbhviewstate; /**< view mode for debugging. 0- nothing 1-only hero 2-only hitbox 3-hero+hitbox */
		friend class RBC_CKeyBinder; /**< For binding player keys*/
	public:
		static void RBC_InitHeroes(void); /**< Initialization of heroes without bitmaps and xmls */
		static void RBC_InitMaps(void);
		static void RBC_LoadMap(int number); /**< Initialization of maps without bitmaps */
		static void RBC_InitPlayers(int playernumber, RBC_CHero* hero, bool dir); /**< Initialization of players with heroes, made for gamestate==3 */

		static int RBC_GetCollisionType(RBC_CPlayer* a, RBC_CPlayer* b);

		static bool RBC_CheckCollision(RBC_CHitbox recta, RBC_CHitbox rectb); /**< TODO: Checking collision between two players */

		static void RBC_MainLoop(void); /**< Main loop of application */

		static void RBC_RefreshAll(void); /**< Refreshing players states,  */

		static void RBC_KeyboardHandler(void); /**< Checks if bindings are pressed */

		static bool RBC_IsKeyDown(int key){return RBC_CKeyboard::RBC_KeyDown(key);} /**< Checks if key is down */

		static bool RBC_IsKeyPressed(int key){return RBC_CKeyboard::RBC_KeyPressed(key);} /**< Works once for one key hit */

		static void RBC_BindButtons(); /**< Method of binding keys- especially for players */

		static void RBC_FlipPlayers(void);

		static void RBC_LoadMapsThumbnails(void);

		static void RBC_LoadHeroesThumbnails(void);

		static void RBC_PurgeMapsThumbnails(void);

		static void RBC_PurgeHeroesThumbnails(void);

		static void RBC_DrawAll(void);
};

#endif // RBC_CGAMEMANAGER_H
