#include "CWindow.h"
#include "Core\CInput.h"

namespace Tempest {
	namespace Core {


		//==============================================================================================
		Window::Window()
			: mWndTitle(DEFAULT_WND_TITLE), mClosed(false), mWndDesc(NULL), mWheelDelta(0)
		{
			mWndClass = { 0 };
			mWndRect.left = GetSystemMetrics(SM_CXSCREEN) / 2 - DEFAULT_WND_WIDTH / 2;
			mWndRect.top = GetSystemMetrics(SM_CYSCREEN) / 2 - DEFAULT_WND_HEIGHT / 2;
			mWndRect.right = GetSystemMetrics(SM_CXSCREEN) / 2 + DEFAULT_WND_WIDTH / 2;
			mWndRect.bottom = GetSystemMetrics(SM_CYSCREEN) / 2 + DEFAULT_WND_HEIGHT / 2;


			stringstream ss;
			ss << ENGINE_NAME;
			mClassName = ss.str();

			mInstance = GetModuleHandle(NULL);

			mWndClass.cbSize = sizeof(mWndClass);
			mWndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
			mWndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
			mWndClass.hIcon = LoadIcon(mInstance, MAKEINTRESOURCE(IDI_ICON1));
			mWndClass.hIconSm = LoadIcon(mInstance, MAKEINTRESOURCE(IDI_ICON1));
			mWndClass.hInstance = mInstance;
			mWndClass.lpfnWndProc = staticWinProc;
			mWndClass.lpszClassName = mClassName.c_str();
			mWndClass.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;

			if (RegisterClassEx(&mWndClass) == 0) {
				//NERVUS_ERROR("CWindow: Failed to register window class");
			}

			mInput = new Input(this);
		}
		//==============================================================================================
		Window::~Window(){
			//DestroyWindow(mWndDesc);
			//PostQuitMessage(1);
			//UnregisterClass(mClassName.c_str(), mInstance);
			delete mInput;
		}
		//==============================================================================================
		bool Window::launchWindow(){
			if (mWndDesc != 0){
				//NERVUS_ERROR("CWindow: Window already launched");
				return false;
			}

			mWndDesc = CreateWindow(mClassName.c_str(),
				mWndTitle.c_str(),
				WS_MAXIMIZEBOX | WS_SYSMENU | WS_MINIMIZEBOX | WS_THICKFRAME,
				mWndRect.left, mWndRect.top,
				mWndRect.right - mWndRect.left,
				mWndRect.bottom - mWndRect.top,
				NULL,
				NULL,
				mInstance,
				(void *)this);

			if (mWndDesc == 0){
				//NERVUS_ERROR("CWindow: Failed to create window");
				return false;
			}

			SetWindowLongPtr(mWndDesc, GWL_USERDATA, (long int)this);



			ShowWindow(mWndDesc, SW_SHOWDEFAULT);
			UpdateWindow(mWndDesc);
			ZeroMemory(&mWndMsg, sizeof(mWndMsg));


			return true;
		}
		//==============================================================================================
		bool Window::isClosed(){
			return mClosed;
		}
		//==============================================================================================
		bool Window::processWindow(){
			if (!mClosed){
				if (PeekMessage(&mWndMsg, NULL, 0U, 0U, PM_REMOVE)) {
					TranslateMessage(&mWndMsg);
					DispatchMessage(&mWndMsg);
					return true;
				}
			}
			return false;
		}
		//==============================================================================================
		bool Window::isActive(){
			return (GetForegroundWindow() == mWndDesc);
		}
		//==============================================================================================
		LRESULT Window::winProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam) {
			switch (msg) {
			case WM_CREATE:
				break;
			case WM_MOUSEWHEEL:
				mWheelDelta = GET_WHEEL_DELTA_WPARAM(wparam);
				break;
			case WM_CLOSE:		//This msg is sent when Close button of the window is pressed, so closing can be prevented
				//DestroyWindow(mWndDesc);
				//break;
			case WM_DESTROY:	//This message is sent when the window is being destroyed and cannot be undone
				mClosed = true;
				DestroyWindow(mWndDesc);
				UnregisterClass(mClassName.c_str(), mInstance);
				break;
			default:
				return DefWindowProc(hWnd, msg, wparam, lparam);
			}

			return 0;
		}
		//==============================================================================================
		LRESULT CALLBACK Window::staticWinProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam) {
			//Some hack to use WinAPI within class
			Window* sWnd = 0;

			if (msg == WM_NCCREATE)
				sWnd = (Window*)lparam;
			else
				sWnd = (Window*)GetWindowLongPtr(hWnd, GWL_USERDATA);

			return sWnd->winProc(hWnd, msg, wparam, lparam);
		}
		//==============================================================================================
		//==============================================================================================
		Input* Window::getInput(){
			return mInput;
		}
		//==============================================================================================
		u32 Window::getWindowWidth(){
			return (mWndRect.right - mWndRect.left);
		}
		//==============================================================================================
		u32 Window::getWindowHeight(){
			return (mWndRect.bottom - mWndRect.top);
		}
		//==============================================================================================
		void Window::setWindowTitle(string title){
			mWndTitle = title;
			if (mWndDesc != 0){
				SetWindowText(mWndDesc, title.c_str());
			}
		}
		//==============================================================================================
		void Window::setWindowPos(u32 newPosX, u32 newPosY){
			u32 width = mWndRect.right - mWndRect.left,
				height = mWndRect.bottom - mWndRect.top;

			mWndRect.left = newPosX;
			mWndRect.top = newPosY;
			mWndRect.right = newPosX + width;
			mWndRect.top = newPosY + height;
			if (mWndDesc != 0){
				SetWindowPos(mWndDesc, HWND_NOTOPMOST, newPosX, newPosY, width, height, SWP_DRAWFRAME | SWP_SHOWWINDOW);
			}

		}
		//==============================================================================================
		void Window::setWindowSize(u32 newWidth, u32 newHeight){
			mWndRect.right = mWndRect.left + newWidth;
			mWndRect.top = mWndRect.bottom + newHeight;
			if (mWndDesc != 0){
				SetWindowPos(mWndDesc, HWND_NOTOPMOST, mWndRect.left, mWndRect.bottom,
					newWidth, newHeight, SWP_DRAWFRAME | SWP_SHOWWINDOW);
			}
		}
		//==============================================================================================
		u32 Window::getWheelDelta(){
			u32 delta = mWheelDelta;
			mWheelDelta = 0;
			return delta;
		}
		//==============================================================================================

	}
}