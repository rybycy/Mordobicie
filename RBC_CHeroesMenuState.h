#ifndef RBC_CHEROESMENUSTATE_H
#define RBC_CHEROESMENUSTATE_H
#include "RBC_CState.h"

class RBC_CHeroesMenuState : public RBC_CState /**< For two players */
{
	protected:
		static bool p0locked;
		static bool p1locked;

		static int p0choose;
		static int p1choose;
	public:
};

#endif // RBC_CHEROESMENUSTATE_H
