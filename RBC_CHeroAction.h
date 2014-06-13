#ifndef RBC_CHEROACTION_H
#define RBC_CHEROACTION_H

#include "RBC_CXMLParser.h"
#include "RBC_CEngineFunctions.h"
#include "RBC_CHitbox.h"

#include <SDL/SDL.h>
#include <string>
#include <vector>

#define LIMITER 1001

class RBC_CHeroAction
{
	protected:
	friend class vector;
		std::string actionname; /**< The name of action */

		std::string tree; /**< String made for filling the path of actions (and derivatives) */

		int multipier; /**< Multipier of animations. Every animation has been made with different frame skipping and frame count. This integer regulates differences*/

		int length; /**< For possibility of setting animations length */

		bool repeat; /**< If it's TRUE you can hold a button to perform action many times */

		std::vector<RBC_CHitbox> hitbox;

		std::vector<SDL_Surface*> bitmap;

		static int widestbitmap;

		/**< Buffer variables */
		std::string stringbuff;
		int intbuff;
		char charbuff[100];
		RBC_CHitbox buffhitb;

	public:

		SDL_Surface* RBC_GetActualBitmap(int frame){return bitmap[frame%bitmap.size()];}

		const char* RBC_GetActionName(void){return actionname.c_str();}

		std::vector<RBC_CHitbox> RBC_GetActualHitbox(int frame);

		int RBC_GetSize(void){return bitmap.size();}

		int RBC_GetMultipier(void){return multipier;}

		int RBC_GetLength(void){return length;}

		bool RBC_GetRepeat(void){return repeat;}

		int RBC_GetTheWidestBitmap(void){return widestbitmap;}


		RBC_CHeroAction(void){multipier=2;repeat=0;}

		RBC_CHeroAction(const char *naem);


		void RBC_ReverseActionAnimation(void);

		void RBC_FlipActionAnimation(void);


		void RBC_LoadHitboxes(const char *heroname);

		void RBC_LoadAttribute(const char *heroname, const char *attribute, int *dest);

		void RBC_LoadAttribute(const char *heroname, const char *attribute, bool *dest);

		void RBC_LoadBitmaps(const char *heroname);




};

#endif // RBC_CHEROACTION_H
