#include "CInput.h"
#include "Core\CWindow.h"

namespace Tempest {
	namespace Core {
		//==============================================================================================
		Input::Input(Window* wnd){
			mOriginWnd = wnd;
			//mWndRect = wndRect;
			mKeyState = new i16[KEYSNUMBER];
			mPrevKeyState = new i16[KEYSNUMBER];
			ZeroMemory(mKeyState, sizeof(i16)*KEYSNUMBER);
			ZeroMemory(mPrevKeyState, sizeof(i16)*KEYSNUMBER);
			mMouseWheel = 0;
		}
		//==============================================================================================
		Input::~Input(){
			mOriginWnd = nullptr;
		}
		//==============================================================================================
		void Input::updateInput(){


			if (GetForegroundWindow() == mOriginWnd->mWndDesc){
				//Mouse
				GetCursorPos(&mMousePos);
				ScreenToClient(mOriginWnd->mWndDesc, &mMousePos);
				GetClientRect(mOriginWnd->mWndDesc, &mWndRect);

				if (mMousePos.x < 0 || mMousePos.x > mWndRect.right ||
					mMousePos.y < 0 || mMousePos.y > mWndRect.bottom) {
					mMousePos.x = -1;
					mMousePos.y = -1;
				}

				//Mouse wheel
				mMouseWheel = mOriginWnd->getWheelDelta();


				//Keyboard
				memcpy(mPrevKeyState, mKeyState, sizeof(i16)*KEYSNUMBER);
				for (u32 i = 0; i < KEYSNUMBER; i++){
					mKeyState[i] = GetAsyncKeyState(i);
				}



			}
			else {
				mMousePos.x = -1;
				mMousePos.y = -1;

				for (u32 i = 0; i < KEYSNUMBER; i++){
					mKeyState[i] = 0;
				}
			}
		}
		//==============================================================================================
		//==============================================================================================
		D3DXVECTOR2 Input::getMousePos(){
			return D3DXVECTOR2((float)mMousePos.x, (float)mMousePos.y);
		}
		//==============================================================================================
		bool Input::isKeyDown(u32 keyCode){
			if (mKeyState[keyCode])
				return true;
			else
				return false;
		}
		//==============================================================================================
		bool Input::isKeyUnpressed(u32 keyCode){
			if (mPrevKeyState[keyCode] && !mKeyState[keyCode])
				return true;
			else
				return false;
		}
		//==============================================================================================
		bool Input::isKeyPressed(u32 keyCode){
			if (!mPrevKeyState[keyCode] && mKeyState[keyCode])
				return true;
			else
				return false;
		}
		//==============================================================================================
		bool Input::isWheelMovedUp(){
			if (mMouseWheel > 0)
				return true;
			else
				return false;
		}
		//==============================================================================================
		bool Input::isWheelMovedDown(){
			if (mMouseWheel < 0)
				return true;
			else
				return false;
		}
		//==============================================================================================
	}
}