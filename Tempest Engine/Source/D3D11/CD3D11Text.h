#pragma once 

#pragma once

#include "Core\TempestSharedHeader.h"
#include "D3D11\CD3D11Mesh.h"

namespace Tempest {
	namespace Render {


		struct GraphicFont{
			string SYMBOLS_LIST;
			
			string PICTURE_PATH;
			u32 LETTER_HEIGHT;
			u32 LETTER_WIDTH;
			u32 ROWS;
			u32 COLUMNS;
		};



		const GraphicFont FONTS_MC_EN = { 
			"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789?!;<=>[\\]^_:\"'#%(),.+-/$~&@¹{}*| " ,
			"Source\\mc_eng.bmp",
		8,
		8,
		3,
		38};




		class D3D11Text {
		private:
			D3D11RenderSystem* mRenderSystem;

			GraphicFont mFont;


			string mText;
			f32 mPosX, mPosY;
			f32 mSize;


			bool mCrop;	//Crop empty columns

			Texture* mFontTexture;
			Material* mMaterial;


			vector<MeshVertex> mTextMeshVertices;



		public:
			D3D11Mesh* mTextMesh;

			D3D11Text(D3D11RenderSystem* renderSystem, GraphicFont font);
			~D3D11Text();



			void getLetter(char letter, vector<MeshVertex>*);		//Generates an array of points with needed tex coords for the letter
			void setText(string text, f32 x, f32 y);

			void setCrop(bool crop);

		};
	}
}