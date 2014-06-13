#ifndef RBC_CHEROCOMPLEXACTION_H
#define RBC_CHEROCOMPLEXACTION_H

#include "RBC_CHeroAction.h"
#include "RBC_CPlayerState.h"

#include <math.h>

class RBC_CHeroComplexAction : public RBC_CHeroAction
{
	protected:

	std::vector<RBC_CPlayerState> combination; /**< Combination of states your hero have to perform to do a complex action */

	public:

	bool RBC_IsComplexActionExecuted(std::vector<RBC_CPlayerState> states,bool facedrection);

	RBC_CHeroComplexAction(const char* naem);

	void RBC_LoadHitboxes(const char *heroname);

	void RBC_AddToCombination(int a, int b){RBC_CPlayerState x;x.state=a;x.value=b;combination.push_back(x);}

	void RBC_ReverseActionDirectionCombination(void);
};

#endif // RBC_CHEROCOMPLEXACTION_H
