#ifndef RBC_CHEROSPECIALATTACK_H
#define RBC_CHEROSPECIALATTACK_H

#include "RBC_CHeroBasicAttack.h"
#include "RBC_CPlayerState.h"
#include <vector>

class RBC_CHeroSpecialAttack : public RBC_CHeroBasicAttack
{
	std::vector<RBC_CPlayerState> combination; /**< Combination of states your hero have to perform to do a special attack */

	public:
	bool RBC_IsSpecialAttackExecuted(std::vector<RBC_CPlayerState> states);

	RBC_CHeroSpecialAttack(const char *naem);


	void RBC_AddToCombination(int a, int b){RBC_CPlayerState x;x.state=a;x.value=b;combination.push_back(x);}

	void RBC_PushBackHitbox(int x, int y, int w, int h, int start, int finish, bool offensive, bool defensive);
};

#endif // RBC_CHEROSPECIALATTACK_H
