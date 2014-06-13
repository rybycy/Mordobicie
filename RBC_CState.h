#ifndef RBC_CSTATE_H
#define RBC_CSTATE_H


class RBC_CState
{
	protected:
		void RBC_HandleKeyboard(void);
		void RBC_Draw(void);

	public:
		void RBC_Start(void);
		void RBC_Finish(void);
		void RBC_Update(int framenumber);

};

#endif // RBC_CSTATE_H
