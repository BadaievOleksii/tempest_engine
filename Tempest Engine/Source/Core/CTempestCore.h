#pragma once

#include "TempestSharedHeader.h"

namespace Tempest {
	namespace Core {
		/* 
		Ключевой класс движка. Создается в единственном экземпляре, и через него происходит 
		взаимодействие со всеми системами движка.
		
		Создает "контейнер" для РендерСистемы
		(например, в ВинАПИ это окно).
		
		
		****Можно настраивать частоту апдейта и рендера****
		*/
		class TempestCore{
		private:

			Render::RENDERSYSTEM_TYPE mRenderSystem;
			i32 mUpdateFreq, mRenderFreq;
			bool mIsRunning;

			virtual void initEngine() = 0;
			virtual void updateEngine() = 0;
			virtual void renderEngine() = 0;
		protected:
			Render::RenderSystem* mRenderer;
			Chrono* mChrono;
			Window* mWindow;
			Input* mInput;

		public:

			TempestCore();
			~TempestCore();


			void setWindowParams(string, u32, u32, u32, u32);
			void setRendererParams(Render::RENDERSYSTEM_TYPE);

			//Carefully. Main game loop inside
			void launchCore();
		};
	}
}