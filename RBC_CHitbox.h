#ifndef RBC_CHITBOX_H
#define RBC_CHITBOX_H

/**< It had been a structure before I realized it have to have initialization of all variables */

class RBC_CHitbox
{
public:
	int x, y, w, h; /**< Coordinates + width + height of hitbox rectangle */
	int start, finish; /**< Start- and finish- frame of hitbox*/
	bool offensive; /**< If it's offensive hitbox */
	bool defensive;

	RBC_CHitbox(void){x=0;y=0;w=0;h=0;start=0;finish=0;offensive=0;defensive=0;}
};

#endif // RBC_CHITBOX_H
