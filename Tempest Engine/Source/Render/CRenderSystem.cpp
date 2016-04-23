#include "CRenderSystem.h"
#include "Render\CCamera.h"

namespace Tempest {
	namespace Render {
		//==============================================================================================
		RenderSystem::RenderSystem()
			: mRenderWnd(nullptr), mFullscreen(false), mBufferWidth(0), mBufferHeight(0)
		{
			mCamera = new Camera();
		}
		//==============================================================================================
		RenderSystem::~RenderSystem(){
			delete mCamera;
		}
		//==============================================================================================
	}
}