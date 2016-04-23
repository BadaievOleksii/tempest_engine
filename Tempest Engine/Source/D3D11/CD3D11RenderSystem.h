#pragma once

#include "Core\TempestSharedHeader.h"
#include "Render\CRenderSystem.h"

namespace Tempest {
	namespace Render {
		class D3D11RenderSystem : public RenderSystem {
			friend class D3D11Mesh;
		private:



			D3D_DRIVER_TYPE mDriverType;
			ID3D11Device* mDevice;
			ID3D11DeviceContext* mDeviceContext;
			IDXGISwapChain* mSwapChain;
			ID3D11RenderTargetView* mBackBuffer;
			ID3D11RasterizerState* mRasterizer;
			ID3D11BlendState* mBlendState;



			ID3D11VertexShader* mBasicVShader;
			ID3D11PixelShader* mBasicPShader;

			ID3D11InputLayout* mVertexFormat;

			ID3D11DepthStencilView* mDepthStencilView;
			ID3D11Texture2D* mDepthStencilBuffer;

			ID3D11DepthStencilState* mDepthStencilState3D;	//"Default" 3D depth buffer
			ID3D11DepthStencilState* mDepthStencilState2D;	//"Default" 2D depth buffer
			ID3D11DepthStencilState* mCurrentDSState;


			ID3D11VertexShader* mBasicVShader2;



			//Camera
			struct cbPerObject
			{
				XMMATRIX  WVP;
			};
			ID3D11Buffer* cbPerObjectBuffer;
			cbPerObject cbPerObj;

			XMFLOAT4X4 WVP;
			XMFLOAT4X4 mCurrMatView;


			XMFLOAT4X4 mMatProj2D;	//"Default" 2D projection matrix
			XMFLOAT4X4 mMatProj3D;	//"Default" 3D projection matrix
			XMFLOAT4X4 mCurrMatProj;



			XMFLOAT4 camUp;



			bool loadShaders();




		public:
			XMFLOAT4X4 mCurrMatWorld;
			//XMFLOAT4 camPosition;
			//XMFLOAT4 camTarget;




			D3D11RenderSystem(Core::Window*);
			~D3D11RenderSystem();




			bool launchRenderSystem();

			bool toggleFullscreen();



			void beginRender();
			void endRender();


			void reloadShader();
		};
	}
}