#include "CTempestCore.h"
#include "Core\CWindow.h"
#include "Core\CInput.h"
#include "Core\CChrono.h"
#include "D3D11\CD3D11RenderSystem.h"
#include "D3D11\CD3D11Mesh.h"
#include "Render\CTexture.h"
#include "Render\CMaterial.h"

namespace Tempest {
	namespace Core {
		//==============================================================================================
		TempestCore::TempestCore() : mRenderSystem(Render::RS_EMPTY), mUpdateFreq(-1), mRenderFreq(-1), mIsRunning(false){
			mWindow = new Window();
			mChrono = new Chrono();
		}
		//==============================================================================================
		TempestCore::~TempestCore(){
			delete mChrono;

			delete mRenderer;
			delete mWindow;

			//"Kills" current WinAPI thread
			PostQuitMessage(1);

		}
		//==============================================================================================
		void TempestCore::setWindowParams(string title, u32 posX, u32 posY, u32 width, u32 height){
			mWindow->setWindowTitle(title);
			mWindow->setWindowSize(width, height);
			mWindow->setWindowPos(posX, posY);
		}
		//==============================================================================================
		void TempestCore::setRendererParams(Render::RENDERSYSTEM_TYPE renderer){
			mRenderSystem = renderer;
		}
		//==============================================================================================
		void TempestCore::launchCore(){
			if (!mWindow->launchWindow()){
				//
				return;
			}




			switch (mRenderSystem){
			case Render::RS_D3D9:
				//mRenderer = new Render::D3D9RenderSystem(mMainWnd);
				return;//
				break;
			case Render::RS_D3D11:
				mRenderer = new Render::D3D11RenderSystem(mWindow);
				break;
			default:
				INFO("CTempestCore: No render system");
				return;
			}
			if (!mRenderer->launchRenderSystem()){
				//
				return;
			}


			mInput = mWindow->getInput();



			initEngine();

			

			while (!mWindow->isClosed()){
				if (!mWindow->processWindow()){
					//Сделать частоты апдейта и рендера



					mInput->updateInput();
					updateEngine();






					mRenderer->beginRender();
					renderEngine();
					mRenderer->endRender();

				}
			}
			
		}
		//==============================================================================================
	}
}