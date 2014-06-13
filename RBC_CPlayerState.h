#ifndef RBC_CPLAYERSTATE_H
#define RBC_CPLAYERSTATE_H


class RBC_CPlayerState
{
	public:
		RBC_CPlayerState(void){state=0;value=0;key=0;used=0;time=0;start=0;}
		RBC_CPlayerState(int a){state=0;value=0;key=0;used=0;time=0;start=0;}
		int state; /**< 0- action 1-basic attack 2-special */
		int value; /**< in depedency of state */
		int key;
		int used;
		int time;
		int start;
};

#endif // RBC_CPLAYERSTATE_H
