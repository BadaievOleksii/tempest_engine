#pragma once

#include "TempestSharedHeader.h"

namespace Tempest {
	namespace Core {
		/*
		Класс, представляющий обычное ВинАПИ окно

		Так же содержит класс ввода, так как ввод привязан к окну - если окно не активно, никакого ввода не происходит
		Но ввод необходимо обновлять извне, так как для ввода может быть необходимо лишь некоторое количество обновлений
		в секунду
		
		*/		
		const string DEFAULT_WND_TITLE = "TEMPEST Engine";
		const u32 DEFAULT_WND_WIDTH = 800;
		const u32 DEFAULT_WND_HEIGHT = 600;
		class Window {
			friend class TempestCore;
			//friend class Render::D3D9RenderSystem;
			friend class Render::D3D11RenderSystem;
			friend class Input;
		private:
			WNDCLASSEX mWndClass;
			MSG mWndMsg;
			HWND mWndDesc;
			HINSTANCE mInstance;
			string mClassName;
			RECT mWndRect;


			string mWndTitle;
			bool mClosed;


			u32 mWheelDelta;
			Input* mInput;
			u32 getWheelDelta();


			LRESULT winProc(HWND, UINT, WPARAM, LPARAM);
			static LRESULT CALLBACK staticWinProc(HWND, UINT, WPARAM, LPARAM);


			Window();
			Window(const Window&);
			Window& operator=(const Window&);
			~Window();
		public:

			bool launchWindow();

			bool isClosed();
			bool processWindow();
			bool isActive();
			
			void setWindowTitle(string);
			void setWindowPos(u32, u32);
			void setWindowSize(u32, u32);

			u32 getWindowWidth();
			u32 getWindowHeight();

			Input* getInput();

		};
	}
}