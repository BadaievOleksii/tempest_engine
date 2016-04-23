#pragma once

#include "Core\TempestSharedHeader.h"

namespace Tempest {
	namespace Render {
		class Material {
			friend class D3D9RenderSystem;
			friend class Mesh;
			friend class D3D9Mesh;
			friend class D3D11Mesh;

		private:
			vector<Texture*> mTextures;
		public:
			Material();
			~Material();
			void addTexture(Texture*);
		};
	}
}