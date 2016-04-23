#include "CD3D11RenderSystem.h"
#include "Core\CWindow.h"
#include "Render\CCamera.h"

#include "Core\CChrono.h"

namespace Tempest {
	namespace Render {
		//==============================================================================================
		D3D11RenderSystem::D3D11RenderSystem(Core::Window* wnd)
			: mDriverType(D3D_DRIVER_TYPE_NULL), mDevice(NULL),
			mDeviceContext(NULL), mSwapChain(NULL), mBackBuffer(NULL), mBasicVShader(NULL), mBasicPShader(NULL),
			mVertexFormat(NULL)
		{
			mRenderWnd = wnd;
		}
		//==============================================================================================
		D3D11RenderSystem::~D3D11RenderSystem(){

			mBasicVShader->Release();
			mBasicPShader->Release();

			mSwapChain->Release();
			mBackBuffer->Release();
			mDevice->Release();
			mDeviceContext->Release();
			mVertexFormat->Release();
			mRasterizer->Release();

			mDepthStencilView->Release();
			mDepthStencilBuffer->Release();

			//Camera
			cbPerObjectBuffer->Release();

			//####################################################################################################
			//####################################################################################################


		}
		//==============================================================================================
		bool D3D11RenderSystem::loadShaders(){
			//char buffer[MAX_PATH];
			//GetModuleFileName(NULL, buffer, MAX_PATH);
			//string::size_type pos = string(buffer).find_last_of("\\/");


			ID3D10Blob *VS, *PS, *VS2;
			if (FAILED(D3DCompileFromFile(L"Source\\BasicShader.fx", NULL, NULL, "VShader", "vs_4_0", 0, 0, &VS, NULL))){
				INFO("CD3D11RenderSystem: Failed compiling vertex shader")
			}



			if (FAILED(D3DCompileFromFile(L"Source\\BasicShader.fx", NULL, NULL, "PShader", "ps_4_0", 0, 0, &PS, NULL))){
				INFO("CD3D11RenderSystem: Failed compiling pixel shader")
			}


			mDevice->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &mBasicVShader);



			mDevice->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &mBasicPShader);


			mDeviceContext->VSSetShader(mBasicVShader, 0, 0);
			mDeviceContext->PSSetShader(mBasicPShader, 0, 0);


			D3D11_INPUT_ELEMENT_DESC layout[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			mDevice->CreateInputLayout(layout, 3, VS->GetBufferPointer(), VS->GetBufferSize(), &mVertexFormat);
			mDeviceContext->IASetInputLayout(mVertexFormat);


			return true;
		}
		//==============================================================================================
		void D3D11RenderSystem::beginRender(){
			mDeviceContext->ClearRenderTargetView(mBackBuffer, D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
			mDeviceContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);



			mCamera->updateCam();
			mCurrMatView._11 = mCamera->mViewMat._11;
			mCurrMatView._21 = mCamera->mViewMat._21;
			mCurrMatView._31 = mCamera->mViewMat._31;
			mCurrMatView._41 = mCamera->mViewMat._41;

			mCurrMatView._12 = mCamera->mViewMat._12;
			mCurrMatView._22 = mCamera->mViewMat._22;
			mCurrMatView._32 = mCamera->mViewMat._32;
			mCurrMatView._42 = mCamera->mViewMat._42;

			mCurrMatView._13 = mCamera->mViewMat._13;
			mCurrMatView._23 = mCamera->mViewMat._23;
			mCurrMatView._33 = mCamera->mViewMat._33;
			mCurrMatView._43 = mCamera->mViewMat._43;

			mCurrMatView._14 = mCamera->mViewMat._14;
			mCurrMatView._24 = mCamera->mViewMat._24;
			mCurrMatView._34 = mCamera->mViewMat._34;
			mCurrMatView._44 = mCamera->mViewMat._44;


			reloadShader();
			


		}
		//==============================================================================================
		void D3D11RenderSystem::endRender(){
			mSwapChain->Present(0, 0);
		}
		//==============================================================================================
		void D3D11RenderSystem::reloadShader(){			
			XMMATRIX wvp = XMLoadFloat4x4(&mCurrMatWorld) * XMLoadFloat4x4(&mCurrMatView) * XMLoadFloat4x4(&mCurrMatProj);
			cbPerObj.WVP = XMMatrixTranspose(wvp);

			mDeviceContext->UpdateSubresource(cbPerObjectBuffer, 0, NULL, &cbPerObj, 0, 0);
			mDeviceContext->VSSetConstantBuffers(0, 1, &cbPerObjectBuffer);
		}
		//==============================================================================================
		//==============================================================================================		
		bool D3D11RenderSystem::toggleFullscreen(){
			//mFullscreen = !mFullscreen;
			//mSwapChain->SetFullscreenState(mFullscreen, NULL);


			mDeviceContext->VSSetShader(mBasicVShader2, 0, 0);///////

			return true;
		}
		//==============================================================================================
		bool D3D11RenderSystem::launchRenderSystem(){
			mBufferWidth = mRenderWnd->getWindowWidth();//GetSystemMetrics(SM_CXSCREEN);
			mBufferHeight = mRenderWnd->getWindowHeight();//GetSystemMetrics(SM_CYSCREEN);

			DXGI_SWAP_CHAIN_DESC scd;
			ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

			scd.BufferCount = 1;
			scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			scd.BufferDesc.Width = mBufferWidth;
			scd.BufferDesc.Height = mBufferHeight;
			scd.BufferDesc.RefreshRate.Numerator = 60;
			scd.BufferDesc.RefreshRate.Denominator = 1;
			scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
			scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;




			scd.SampleDesc.Count = 1;
			scd.SampleDesc.Quality = 0;
			scd.BufferCount = 1;
			scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

			scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			scd.OutputWindow = mRenderWnd->mWndDesc;
			scd.Windowed = TRUE;
			scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;




			D3D11CreateDeviceAndSwapChain(NULL,
				D3D_DRIVER_TYPE_HARDWARE,
				NULL,
				NULL,
				NULL,
				NULL,
				D3D11_SDK_VERSION,
				&scd,
				&mSwapChain,
				&mDevice,
				NULL,
				&mDeviceContext);



			ID3D11Texture2D *pBackBuffer;
			mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

			mDevice->CreateRenderTargetView(pBackBuffer, NULL, &mBackBuffer);
			pBackBuffer->Release();




			//Rasterizer
			D3D11_RASTERIZER_DESC wfdesc;
			ZeroMemory(&wfdesc, sizeof(D3D11_RASTERIZER_DESC));
			wfdesc.FillMode = D3D11_FILL_SOLID;//_WIREFRAME
			wfdesc.CullMode = D3D11_CULL_NONE;//_BACK, _NONE, _FRONT
			mDevice->CreateRasterizerState(&wfdesc, &mRasterizer);
			mDeviceContext->RSSetState(mRasterizer);


			//Blending
			D3D11_BLEND_DESC blendDesc;
			ZeroMemory(&blendDesc, sizeof(blendDesc));

			D3D11_RENDER_TARGET_BLEND_DESC rtbd;
			ZeroMemory(&rtbd, sizeof(rtbd));

			rtbd.BlendEnable = true;
			rtbd.SrcBlend = D3D11_BLEND_SRC_ALPHA;
			rtbd.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
			rtbd.BlendOp = D3D11_BLEND_OP_ADD;
			rtbd.SrcBlendAlpha = D3D11_BLEND_INV_DEST_ALPHA;
			rtbd.DestBlendAlpha = D3D11_BLEND_ONE;
			rtbd.BlendOpAlpha = D3D11_BLEND_OP_ADD;
			rtbd.RenderTargetWriteMask = D3D10_COLOR_WRITE_ENABLE_ALL;

			blendDesc.AlphaToCoverageEnable = false;
			blendDesc.RenderTarget[0] = rtbd;

			mDevice->CreateBlendState(&blendDesc, &mBlendState);



			float blendFactor[] = { 0.75f, 0.75f, 0.75f, 1.0f };
			mDeviceContext->OMSetBlendState(mBlendState, blendFactor, 0xffffffff);




			//Stencil buffer
			D3D11_TEXTURE2D_DESC depthStencilDesc;

			depthStencilDesc.Width = mBufferWidth;
			depthStencilDesc.Height = mBufferHeight;
			depthStencilDesc.MipLevels = 1;
			depthStencilDesc.ArraySize = 1;
			depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			depthStencilDesc.SampleDesc.Count = 1;
			depthStencilDesc.SampleDesc.Quality = 0;
			depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
			depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			depthStencilDesc.CPUAccessFlags = 0;
			depthStencilDesc.MiscFlags = 0;

			mDevice->CreateTexture2D(&depthStencilDesc, NULL, &mDepthStencilBuffer);

			mDevice->CreateDepthStencilView(mDepthStencilBuffer, NULL, &mDepthStencilView);

			mDeviceContext->OMSetRenderTargets(1, &mBackBuffer, mDepthStencilView);


			D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc;
			ZeroMemory(&depthStencilStateDesc, sizeof(depthStencilStateDesc));

			depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_LESS;

			depthStencilStateDesc.StencilEnable = true;
			depthStencilStateDesc.StencilReadMask = 0xFF;
			depthStencilStateDesc.StencilWriteMask = 0xFF;

			depthStencilStateDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			depthStencilStateDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
			depthStencilStateDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			depthStencilStateDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;


			depthStencilStateDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			depthStencilStateDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
			depthStencilStateDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			depthStencilStateDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;


			depthStencilStateDesc.DepthEnable = true;
			mDevice->CreateDepthStencilState(&depthStencilStateDesc, &mDepthStencilState3D);

			depthStencilStateDesc.DepthEnable = false;
			mDevice->CreateDepthStencilState(&depthStencilStateDesc, &mDepthStencilState2D);



			mCurrentDSState = mDepthStencilState3D;
			mDeviceContext->OMSetDepthStencilState(mCurrentDSState, 1);







			//Viewport
			D3D11_VIEWPORT viewport;
			ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

			//Splitscreen here
			viewport.TopLeftX = 0;
			viewport.TopLeftY = 0;
			viewport.MinDepth = 0.0f;
			viewport.MaxDepth = 1.0f;
			viewport.Width = (f32)mBufferWidth;
			viewport.Height = (f32)mBufferHeight;

			mDeviceContext->RSSetViewports(1, &viewport);




			loadShaders();




			//Create the buffer to send to the cbuffer in effect file
			D3D11_BUFFER_DESC cbbd;
			ZeroMemory(&cbbd, sizeof(D3D11_BUFFER_DESC));

			cbbd.Usage = D3D11_USAGE_DEFAULT;
			cbbd.ByteWidth = sizeof(cbPerObject);
			cbbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			cbbd.CPUAccessFlags = 0;
			cbbd.MiscFlags = 0;

			mDevice->CreateBuffer(&cbbd, NULL, &cbPerObjectBuffer);

			


			XMStoreFloat4x4(&mCurrMatWorld, XMMatrixIdentity());



			XMStoreFloat4x4(&mMatProj3D, XMMatrixPerspectiveFovLH(D3DXToRadian(60), (f32)mBufferWidth / mBufferHeight, 1.0f, 100.0f));

			//0;0 at center
			XMStoreFloat4x4(&mMatProj2D, XMMatrixOrthographicOffCenterLH(-(mBufferWidth / 2.0f), (mBufferWidth / 2.0f),
				-(mBufferHeight / 2.0f), mBufferHeight / 2.0f, 0.1f, 100.0f));


			mCurrMatProj = mMatProj3D;


			//0;0 at left-bottom
			//XMStoreFloat4x4(&matProj2d, XMMatrixOrthographicOffCenterLH(0.0f, mBufferWidth, 
			//	0.0f, mBufferHeight, 0.1f, 100.0f));


			//XMStoreFloat4x4(&matProj2d, XMMatrixOrthographicOffCenterLH(0.0f, mBufferWidth,
			//	0.0f, mBufferHeight, 0.1f, 100.0f));



			//0;0 at left-top, but Y must be negative
			//XMStoreFloat4x4(&matProj2d, XMMatrixOrthographicOffCenterLH(0.0f, mBufferWidth,
			//	-(f32)mBufferHeight, 0.0f, 0.1f, 100.0f));


			//XMStoreFloat4x4(&matProj2d, XMMatrixOrthographicOffCenterLH(0.0f, mBufferWidth,
			//	mBufferHeight, 0.0f, 0.1f, 100.0f));


















			//####################################################################################################
			//#########################################TEST#######################################################










			return true;
		}
		//==============================================================================================
	}
}