#pragma once

#include "Core\TempestSharedHeader.h"

namespace Tempest {
	namespace Render {
		class RenderSystem{
		private:
		protected:
			u32 mBufferWidth, mBufferHeight;
			Core::Window* mRenderWnd;
			bool mFullscreen;
		public:
			Camera* mCamera;

			RenderSystem();
			virtual ~RenderSystem();

			virtual bool launchRenderSystem() = 0;



			virtual void beginRender() = 0;
			virtual void endRender() = 0;

		};
	}
}