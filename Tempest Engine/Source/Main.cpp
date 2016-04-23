#include "Core\TempestStdIncludes.h"
#include "Core\TempestTypes.h"
#include "Core\CWindow.h"
#include "Core\TempestLogging.h"
#include "Core\CChrono.h"
#include "Core\CInput.h"
#include "Core\CTempestCore.h"


#include "Render\CCamera.h"
#include "Render\CRenderSystem.h"
#include "Render\CTexture.h"
#include "Render\CMaterial.h"
#include "D3D11\CD3D11RenderSystem.h"
#include "D3D11\CD3D11Mesh.h"
#include "D3D11\CD3D11Text.h"


using namespace Tempest;
using namespace Tempest::Core;
using namespace Tempest::Render;


class TempestEngine : public TempestCore{
	Mesh* mesh1;
	Mesh* mesh2;
	
	D3D11Text* t;
	D3D11Text* t2;


	XMFLOAT4X4 cube1World;
	XMFLOAT4X4 cube2World;
	XMFLOAT4X4 Rotation;
	XMFLOAT4X4 Scale;
	XMFLOAT4X4 Translation;
	f32 rot = 0.01f;

	D3D11RenderSystem* r;

	//==============================================================================================
	void initEngine(){
		r = (D3D11RenderSystem*)mRenderer;


		//Цельный алгоритм загрузки меша с текстурой:
		Texture* tex1 = new Texture("Source\\aquafish01.bmp");
		tex1->loadImageFromFile();
		Material* mat1 = new Material();
		mat1->addTexture(tex1);

		mesh1 = new D3D11Mesh(r);
		mesh1->setMaterial(mat1);

		mesh1->loadMeshFromObj("Source\\aquafish01.obj");
		




		mesh2 = new D3D11Mesh((D3D11RenderSystem*)mRenderer);
		mesh2->setMaterial(mat1);

		mesh2->loadMeshFromObj("Source\\aquafish01.obj");








		t = new D3D11Text(r, FONTS_MC_EN);
		t2 = new D3D11Text(r, FONTS_MC_EN);
		t2->setCrop(false);

		stringstream ss;
		ss << "aAH_:\"'%(),.+-/$~&@№{}*| ";
		t->setText(ss.str(), -400.0f, 240.0f);
		t2->setText(ss.str(), -400.0f, 140.0f);
	}
	//==============================================================================================
	void updateEngine(){
		if (mInput->isKeyPressed(Input::KEY_T)){
			//mRenderer->toggleFullscreen();
		}
		if (mInput->isKeyDown(Input::KEY_T)){

		}

		if (mInput->isWheelMovedUp()){
			mRenderer->mCamera->forwardCam(CAMERA_MOVE * 5.0f);
		}

		if (mInput->isWheelMovedDown()){
			mRenderer->mCamera->forwardCam(-CAMERA_MOVE * 5.0f);
		}

		if (mInput->isKeyDown(Input::KEY_D)){
			mRenderer->mCamera->strafeCam(CAMERA_MOVE * 0.05f);
		}
		if (mInput->isKeyDown(Input::KEY_A)){
			mRenderer->mCamera->strafeCam(-CAMERA_MOVE * 0.05f);
		}

		if (mInput->isKeyDown(Input::KEY_W)){
			mRenderer->mCamera->upCam(CAMERA_MOVE * 0.05f);
		}
		if (mInput->isKeyDown(Input::KEY_S)){
			mRenderer->mCamera->upCam(-CAMERA_MOVE * 0.05f);
		}
		if (mInput->isKeyDown(Input::KEY_E)){
			mRenderer->mCamera->yawCam(CAMERA_ROTATE * 0.05f);
		}
		if (mInput->isKeyDown(Input::KEY_Q)){
			mRenderer->mCamera->yawCam(-CAMERA_ROTATE * 0.05f);
		}





		//Перенести внутрь меша
		rot += .0005f;
		if (rot > 6.28f)
			rot = 0.0f;

		XMStoreFloat4x4(&cube1World, XMMatrixIdentity());

		XMFLOAT4 rotaxis;
		XMStoreFloat4(&rotaxis, XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));


		XMStoreFloat4x4(&Rotation, XMMatrixRotationAxis(XMLoadFloat4(&rotaxis), rot));
		XMStoreFloat4x4(&Translation, XMMatrixTranslation(10.0f, 0.0f, -4.0f));

		XMStoreFloat4x4(&cube1World, XMLoadFloat4x4(&Translation) * XMLoadFloat4x4(&Rotation));

		XMStoreFloat4x4(&cube2World, XMMatrixIdentity());

		XMStoreFloat4x4(&Rotation, XMMatrixRotationAxis(XMLoadFloat4(&rotaxis), -rot));
		XMStoreFloat4x4(&Scale, XMMatrixScaling(0.6f, 0.6f, 0.6f));

		XMStoreFloat4x4(&cube2World, XMLoadFloat4x4(&Rotation) * XMLoadFloat4x4(&Scale));


	}
	//==============================================================================================
	void renderEngine(){

		r->mCurrMatWorld = cube2World;
		mesh2->renderMesh();
		r->mCurrMatWorld = cube1World;
		mesh1->renderMesh();


		XMStoreFloat4x4(&r->mCurrMatWorld, XMMatrixIdentity());
		t->mTextMesh->renderMesh();
		t2->mTextMesh->renderMesh();
	}
	//==============================================================================================
};




int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){


	/*
	
	План:
	
	Доделать текст:
	доделать "сжатие" букв (косяк в определении пустого столбца)





	Подумать куда втулить материал и текстуры
	Допилить камеру (сделать норм изменение точки куда она смотрит), сделать привязку камеры
	Подумать ещё над компонентной моделью и как с ней связать меши
	
	
	
	
	*/

	 


	TempestEngine* core = new TempestEngine();
	//core->setWindowParams();
	core->setRendererParams(Render::RS_D3D11);
	core->launchCore();


	delete core;
	
	return 1;
}