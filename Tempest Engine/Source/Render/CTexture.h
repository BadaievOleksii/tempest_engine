#pragma once

#include "Core\TempestSharedHeader.h"

namespace Tempest {
	namespace Render {

		union PixelData{
			u32 argb;
			u8 a, r, g, b;
		};

		class Texture {
			friend class D3D11Mesh;
			friend class D3D11Text;
		private:;
			string mPath;
			//Array of bytes (ARGB)
			u8* mImageData;
			//Original image size
			u32 mImageWidth, mImageHeight;
			u32 mImageSize;
			bool mLoaded;
		
			bool loadFromBMP();
		public:
			bool loadImageFromFile();

			Texture(string);
			~Texture();

		};
	}
}