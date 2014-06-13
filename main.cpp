#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include <vector>

#define OUTPUT 1

#include "RBC_CEngineFunctions.h"
#include "RBC_CGameManager.h"

int main ( int argc, char** argv )
{
    RBC_CEngineFunctions::RBC_InitEverything();

	RBC_CGameManager::RBC_MainLoop();

	/**< TODO: Cleaning after all  */

	return 0;
}
