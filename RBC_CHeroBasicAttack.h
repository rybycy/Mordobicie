#ifndef RBC_CHEROBASICATTACK_H
#define RBC_CHEROBASICATTACK_H

#include "RBC_CHeroAction.h"

class RBC_CHeroBasicAttack : public RBC_CHeroAction
{

protected:
		int damage;
		bool knockdown;

public:
		int RBC_GetDamage(void){return damage;}

		RBC_CHeroBasicAttack(void){multipier=2;repeat=0;}
		RBC_CHeroBasicAttack(const char *naem);


		void RBC_SetDamage(int x){damage=x;}

		void RBC_SetMultipier(int x){multipier=x;}


		void RBC_LoadHitboxes(const char *naem);

};

#endif // RBC_CHEROBASICATTACK_H
