#include "CD3D11Text.h"
#include "Render\CMaterial.h"
#include "Render\CTexture.h"
#include "D3D11\CD3D11RenderSystem.h"


namespace Tempest {
	namespace Render {




		//==============================================================================================
		D3D11Text::D3D11Text(D3D11RenderSystem* renderSystem, GraphicFont font) :
			mRenderSystem(renderSystem), mTextMesh(nullptr), mPosX(0.0f), mPosY(0.0f), mSize(20.0f), mCrop(true)
		{
			mFont = font;
			mFontTexture = new Texture(mFont.PICTURE_PATH);
			mFontTexture->loadImageFromFile();
			mMaterial = new Material();
			mMaterial->addTexture(mFontTexture);

			for (u32 b = 0; b < mFontTexture->mImageSize; b += 4){
				if (mFontTexture->mImageData[b + 1] == 0 
					&& mFontTexture->mImageData[b + 2] == 0 
					&& mFontTexture->mImageData[b + 3] == 0){

					mFontTexture->mImageData[b] = 0;	//Makes black pixels transparent
				}
			}

		}
		//==============================================================================================
		D3D11Text::~D3D11Text(){
			if (mTextMesh)
				delete mTextMesh;
			if (mMaterial)
				delete mMaterial;
			if (mFontTexture)
				delete mFontTexture;
		}
		//==============================================================================================
		//==============================================================================================
		void D3D11Text::getLetter(char letter, vector<MeshVertex>* vrts){
			f32 letterStepColumn = 1.0f / mFont.COLUMNS;
			f32 letterStepRow = 1.0f / mFont.ROWS;

			u32 letterPos = 0;

			while(letterPos < mFont.SYMBOLS_LIST.size()){
				if (mFont.SYMBOLS_LIST.at(letterPos) == letter)
					break;
				letterPos++;
			}


			if (letterPos == mFont.SYMBOLS_LIST.size()){
				//letterPos--;
				//INFO("CD3D11Text: Letter not found " << letterPos);
			}

			vrts->clear();


			MeshVertex temp;

			f32 x1 = (letterPos %  mFont.COLUMNS)*letterStepColumn;
			f32 x2 = (letterPos %  mFont.COLUMNS + 1.0f)*letterStepColumn;

			f32 y1 = (letterPos / mFont.COLUMNS)*letterStepRow;
			f32 y2 = (letterPos / mFont.COLUMNS + 1.0f)*letterStepRow;

			f32 newWidth = mSize;

			if (mCrop){
				u32 emptyCols = 0;
				u32 x = (letterPos %  mFont.COLUMNS)*mFont.LETTER_WIDTH;
				u32 y = (letterPos / mFont.COLUMNS)*mFont.LETTER_HEIGHT;
				u32 clearPixels = 0;

				for (int c = x; c < (x + mFont.LETTER_WIDTH); c++){
				//for (int c = x + mFont.LETTER_WIDTH - 1; c >= x; c--){
					clearPixels = 0;
					for (int i = y; i < (y + mFont.LETTER_HEIGHT); i++){
						/*if (mFontTexture->mImageData[i*mFontTexture->mImageWidth * 4 + c * 4 + 1] != 0
							|| mFontTexture->mImageData[i*mFontTexture->mImageWidth * 4 + c * 4 + 2] != 0
							|| mFontTexture->mImageData[i*mFontTexture->mImageWidth * 4 + c * 4 + 3] != 0)*/
						if (mFontTexture->mImageData[i*mFontTexture->mImageWidth * 4 + c * 4] == 0)
						{
							clearPixels++;
						}

					}

					if (clearPixels == mFont.LETTER_HEIGHT){
						emptyCols++;
					}
				}
				if (letter == ' '){
					emptyCols = 0;
				}

				if (emptyCols > 1){
					emptyCols--;
					x2 -= (1.0f / (mFont.COLUMNS*mFont.LETTER_WIDTH))*emptyCols;
					newWidth -= (mSize / mFont.LETTER_WIDTH)*emptyCols;
				}

			}


			temp = { 0.0f, mSize, 4.0f, x1, y1 };
			vrts->push_back(temp);
			temp = { newWidth, mSize, 4.0f, x2, y1 };
			vrts->push_back(temp);
			temp = { 0.0f, 0.0f, 4.0f, x1, y2 };
			vrts->push_back(temp);

			temp = { newWidth, mSize, 4.0f, x2, y1 };
			vrts->push_back(temp);
			temp = { newWidth, 0.0f, 4.0f, x2, y2 };
			vrts->push_back(temp);
			temp = { 0.0f, 0.0f, 4.0f, x1, y2 };
			vrts->push_back(temp);





			temp = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };//Blank vertex cause vector somehow "eats" two last floats
			vrts->push_back(temp);




			//return vertices;

		}
		//==============================================================================================
		void D3D11Text::setText(string text, f32 x, f32 y){
			mTextMeshVertices.reserve(text.size() * 6 + 1);//Two triangles = 6 vertices + 1 extra
			mPosX = x;
			mPosY = y;
			f32 mSumX = 0.0f; 
			f32 prevX = 0.0f;

			vector<MeshVertex> letter;

			for (u32 i = 0; i < text.size(); i++){
				//if (i > 0)
				mSumX += prevX + 10.0;
				getLetter(text.at(i), &letter);
				prevX = letter[1].x;
				for (u32 v = 0; v < 6; v++){
					letter[v].x += mSumX + mPosX;
					letter[v].y += mPosY;
				}
				for (u32 v = 0; v < 6; v++){
					mTextMeshVertices.push_back(letter[v]);
				}
			}

			mTextMeshVertices.push_back({ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f });





			if (mTextMesh)
				delete mTextMesh;
			mTextMesh = new D3D11Mesh(mRenderSystem);
			mTextMesh->setMaterial(mMaterial);


			mTextMesh->loadMeshFromArray(mTextMeshVertices);

			mTextMesh->mNoDepth = true;
			mTextMesh->mNotMoving = true;
			mTextMesh->mOrthoProj = true;
		}
		//==============================================================================================
		//==============================================================================================
		void D3D11Text::setCrop(bool crop){
			mCrop = crop;
		}
	}
}