#define _CRT_SECURE_NO_WARNINGS

#include "CTexture.h"

#include "Render\CRenderSystem.h"

namespace Tempest {
	namespace Render {
		//==============================================================================================
		Texture::Texture(string path)
			: mPath(path), mImageWidth(0), mImageHeight(0), mImageSize(0), mLoaded(false)
		{
			//loadImageFromFile();
		}
		//==============================================================================================
		Texture::~Texture(){
			delete[] mImageData;
		}
		//==============================================================================================
		//==============================================================================================
		bool Texture::loadFromBMP(){
			u8 header[54]; // Each BMP file begins by a 54-bytes header

			FILE* image = fopen(mPath.c_str(), "rb");

			if (fread(header, 1, 54, image) != 54){ 
				return false;
			}
			mImageWidth = *(u32*)&(header[0x12]);
			mImageHeight = *(u32*)&(header[0x16]);
			mImageSize = mImageWidth * mImageHeight * 4;

			mImageData = new u8[mImageSize];


			//BMP-24 stores color as [B-G-R] without Alpha byte
			for (u32 b = 0; b < mImageSize; b += 4){
				mImageData[b] = 0xFF;		//To Alpha-byte
				fread(&mImageData[b + 3], 1, 1, image);	//To B-color byte
				fread(&mImageData[b + 2], 1, 1, image);	//To G-color byte
				fread(&mImageData[b + 1], 1, 1, image);	//To R-color byte
				//Order of calls is essential
			}
			fclose(image);
			mLoaded = true;

			return true;
		}
		//==============================================================================================
		bool Texture::loadImageFromFile(){
			if (mLoaded){
				return true;
			}


			if (mPath == ""){
				return false;
			}

			u8 type[2];
			FILE* image = fopen(mPath.c_str(), "rb");
			fread(type, 1, 2, image);
			fclose(image);

			if (type[0] == 'B' || type[1] == 'M'){
				return loadFromBMP();
			}
			



			INFO("CTexture: Image has unsupported format");
			return false;
		}
		//==============================================================================================
	}
}