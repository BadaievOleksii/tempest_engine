#pragma once


#include "Core\TempestSharedHeader.h"

namespace Tempest {
	namespace Core {

		
		class Input {
			friend class Window;
		private:
			Window* mOriginWnd;
			POINT mMousePos;
			RECT mWndRect;


			i16* mKeyState;
			i16* mPrevKeyState;

			i32 mMouseWheel;

			Input(Window* wnd);


			Input();
			Input(const Input& root);
			Input& operator=(const Input&);

			
			~Input();


		public:

			void updateInput();
			//Returns mouse position within the window
			//If mouse is out of the window, returns (-1;-1)
			D3DXVECTOR2 getMousePos();
			//Is key down for now
			bool isKeyDown(u32 keyCode);

			//Turns to true for 1 logic tick when key was unpressed 
			bool isKeyUnpressed(u32 keyCode);
			//Turns to true for 1 logic tick when key was pressed
			bool isKeyPressed(u32 keyCode);

			//Turns to true for 1 logic tick when mouse wheel was moved up (FROM the user)
			bool isWheelMovedUp();
			//Turns to true for 1 logic tick when mouse wheel was moved down (TO the user)
			bool isWheelMovedDown();




			static const u32 KEYSNUMBER = 256;

			static const u32 KEY_0 = 0x30;
			static const u32 KEY_1 = 0x31;
			static const u32 KEY_2 = 0x32;
			static const u32 KEY_3 = 0x33;
			static const u32 KEY_4 = 0x34;
			static const u32 KEY_5 = 0x35;
			static const u32 KEY_6 = 0x36;
			static const u32 KEY_7 = 0x37;
			static const u32 KEY_8 = 0x38;
			static const u32 KEY_9 = 0x39;

			static const u32 KEY_A = 0x41;
			static const u32 KEY_B = 0x42;
			static const u32 KEY_C = 0x43;
			static const u32 KEY_D = 0x44;
			static const u32 KEY_E = 0x45;
			static const u32 KEY_F = 0x46;
			static const u32 KEY_G = 0x47;
			static const u32 KEY_H = 0x48;
			static const u32 KEY_I = 0x49;
			static const u32 KEY_J = 0x4A;
			static const u32 KEY_K = 0x4B;
			static const u32 KEY_L = 0x4C;
			static const u32 KEY_M = 0x4D;
			static const u32 KEY_N = 0x4E;
			static const u32 KEY_O = 0x4F;
			static const u32 KEY_P = 0x50;
			static const u32 KEY_Q = 0x51;
			static const u32 KEY_R = 0x52;
			static const u32 KEY_S = 0x53;
			static const u32 KEY_T = 0x54;
			static const u32 KEY_U = 0x55;
			static const u32 KEY_V = 0x56;
			static const u32 KEY_W = 0x57;
			static const u32 KEY_X = 0x58;
			static const u32 KEY_Y = 0x59;
			static const u32 KEY_Z = 0x5A;

			static const u32 KEY_PGUP = 0x21;
			static const u32 KEY_PGDOWN = 0x22;
			static const u32 KEY_END = 0x23;
			static const u32 KEY_HOME = 0x24;
			static const u32 KEY_INSERT = 0x2D;
			static const u32 KEY_DELETE = 0x2E;

			static const u32 KEY_ARROWLEFT = 0x25;
			static const u32 KEY_ARROWUP = 0x26;
			static const u32 KEY_ARROWRIGHT = 0x27;
			static const u32 KEY_ARROWDOWN = 0x28;

			static const u32 KEY_PRINTSCR = 0x2C;
			static const u32 KEY_PAUSE = 0x13;

			static const u32 KEY_F1 = 0x70;
			static const u32 KEY_F2 = 0x71;
			static const u32 KEY_F3 = 0x72;
			static const u32 KEY_F4 = 0x73;
			static const u32 KEY_F5 = 0x74;
			static const u32 KEY_F6 = 0x75;
			static const u32 KEY_F7 = 0x76;
			static const u32 KEY_F8 = 0x77;
			static const u32 KEY_F9 = 0x78;
			static const u32 KEY_F10 = 0x79;
			static const u32 KEY_F11 = 0x7A;
			static const u32 KEY_F12 = 0x7B;

			static const u32 KEY_NUMPAD0 = 0x60;
			static const u32 KEY_NUMPAD1 = 0x61;
			static const u32 KEY_NUMPAD2 = 0x62;
			static const u32 KEY_NUMPAD3 = 0x63;
			static const u32 KEY_NUMPAD4 = 0x64;
			static const u32 KEY_NUMPAD5 = 0x65;
			static const u32 KEY_NUMPAD6 = 0x66;
			static const u32 KEY_NUMPAD7 = 0x67;
			static const u32 KEY_NUMPAD8 = 0x68;
			static const u32 KEY_NUMPAD9 = 0x69;
			static const u32 KEY_NUMPAD_MUL = 0x6A;
			static const u32 KEY_NUMPAD_ADD = 0x6B;
			static const u32 KEY_NUMPAD_SEP = 0x6C;
			static const u32 KEY_NUMPAD_SUB = 0x6D;
			static const u32 KEY_NUMPAD_DOT = 0x6E;
			static const u32 KEY_NUMPAD_DIV = 0x6F;

			static const u32 KEY_NUMLOCK = 0x90;
			static const u32 KEY_SCRLOCK = 0x91;
			static const u32 KEY_CAPSLOCK = 0x14;

			static const u32 KEY_LSHIFT = 0xA0;
			static const u32 KEY_RSHIFT = 0xA1;
			static const u32 KEY_LCONTROL = 0xA2;
			static const u32 KEY_RCONTROL = 0xA3;
			static const u32 KEY_LMENU = 0xA4;
			static const u32 KEY_RMENU = 0xA5;

			static const u32 KEY_BACKSPACE = 0x08;
			static const u32 KEY_TAB = 0x09;
			static const u32 KEY_ENTER = 0x0D;
			static const u32 KEY_SPACE = 0x20;
			static const u32 KEY_ESCAPE = 0x1B;



			static const u32 KEY_LEFT = 0x01;
			static const u32 KEY_RIGHT = 0x02;
			static const u32 KEY_MIDDLE = 0x04;
		};
	}
}