#include "CD3D11Mesh.h"
#include "Render\CMaterial.h"
#include "Render\CTexture.h"
#include "D3D11\CD3D11RenderSystem.h"

namespace Tempest {
	namespace Render {
		//==============================================================================================
		D3D11Mesh::D3D11Mesh(D3D11RenderSystem* renderSystem)
			: mRenderSystem(renderSystem), mVertexBuffer(nullptr), mIndexBuffer(nullptr), mTextureView(nullptr),
			mTexSamplerState(nullptr), mTexture(nullptr)
		{

			

		}
		//==============================================================================================
		D3D11Mesh::~D3D11Mesh(){
			mVertexBuffer->Release();
			mIndexBuffer->Release();
		}
		//==============================================================================================
		bool D3D11Mesh::createBuffers(){
			//Загрузка модели



			//Hresult
			HRESULT hr;

			// Заполняем вершинный буфер
			D3D11_BUFFER_DESC bd;
			ZeroMemory(&bd, sizeof(bd));
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(D3D11MeshVertex)* mVertices.size();
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = 0;
			bd.MiscFlags = 0;
			D3D11_SUBRESOURCE_DATA InitData;
			InitData.pSysMem = &(mVertices[0]);
			hr = mRenderSystem->mDevice->CreateBuffer(&bd, &InitData, &mVertexBuffer);
			if (FAILED(hr))
				return hr;

			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(DWORD)* mIndCount;
			bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bd.CPUAccessFlags = 0;
			bd.MiscFlags = 0;
			InitData.pSysMem = &(mIndices[0]);
			hr = mRenderSystem->mDevice->CreateBuffer(&bd, &InitData, &mIndexBuffer);
			if (FAILED(hr))
				return hr;



			//Загрузка текстуры


			//Loads default texture if none provided
			/////// Поправить
			if (!mMaterial){
				Texture* def = new Texture("F:\\Games\\Programming\\Project\\Media\\DefaultTexture.bmp");
				def->loadImageFromFile();
				mMaterial = new Material();
				mMaterial->addTexture(def);

			}



			//....Multitexturing....
			Texture* tex = mMaterial->mTextures[0];


			u8* revData = new u8[tex->mImageSize];

			for (i32 c = tex->mImageHeight - 1; c >= 0; c--){	//Processes rows
				for (u32 r = 0; r < tex->mImageWidth; r++){		//Processes one row
					/*
					D3D11 has color format RGBA, while Texture stores as ARGB
					Moreover, DirectX reads texture data from the end, so it needs to be reversed
					*/
					revData[c*tex->mImageWidth * 4 + r * 4 + 3] =
						tex->mImageData[(tex->mImageHeight - c - 1)*tex->mImageWidth * 4 + r * 4];//Alpha

					revData[c*tex->mImageWidth * 4 + r * 4] =
						tex->mImageData[(tex->mImageHeight - c - 1)*tex->mImageWidth * 4 + r * 4 + 1];

					revData[c*tex->mImageWidth * 4 + r * 4 + 1] =
						tex->mImageData[(tex->mImageHeight - c - 1)*tex->mImageWidth * 4 + r * 4 + 2];

					revData[c*tex->mImageWidth * 4 + r * 4 + 2] =
						tex->mImageData[(tex->mImageHeight - c - 1)*tex->mImageWidth * 4 + r * 4 + 3];

				}
			}

			D3D11_SUBRESOURCE_DATA sd;
			ZeroMemory(&sd, sizeof(sd));
			sd.pSysMem = revData;
			sd.SysMemPitch = tex->mImageWidth * 4;	//Bytes between each new row

			D3D11_TEXTURE2D_DESC td;
			ZeroMemory(&td, sizeof(td));

			td.Width = tex->mImageWidth;
			td.Height = tex->mImageHeight;
			td.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			td.MipLevels = td.ArraySize = 1;
			td.SampleDesc.Count = 1;
			td.Usage = D3D11_USAGE_DEFAULT;
			td.BindFlags = D3D11_BIND_SHADER_RESOURCE;

			mRenderSystem->mDevice->CreateTexture2D(&td, &sd, &mTexture);

			/*
			D3D11_MAPPED_SUBRESOURCE ms2;
			mRenderSystem->mDeviceContext->Map(mVertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms2);
			memcpy(ms2.pData, tex->mImageData, tex->mImageWidth*tex->mImageHeight*4);
			mRenderSystem->mDeviceContext->Unmap(mVertexBuffer, NULL);
			*/

			mRenderSystem->mDevice->CreateShaderResourceView(mTexture, nullptr, &mTextureView);


			// Describe the Sample State
			D3D11_SAMPLER_DESC sampDesc;
			ZeroMemory(&sampDesc, sizeof(sampDesc));
			sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;//D3D11_FILTER_MIN_MAG_MIP_LINEAR - мыльно увеличивает
			sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
			sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
			sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
			sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
			sampDesc.MinLOD = 0;
			sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
			mRenderSystem->mDevice->CreateSamplerState(&sampDesc, &mTexSamplerState);





			return true;
		}
		//==============================================================================================
		//==============================================================================================
		bool D3D11Mesh::loadMeshFromArray(vector<MeshVertex> vrts){			
			if (mLoaded)
				return false;

			D3D11MeshVertex temp;
			for (u32 i = 0; i < vrts.size(); i++){
				temp.position = { vrts[i].x, vrts[i].y, vrts[i].z };
				temp.normal = { 0.0f, 0.0f, 0.0f };
				temp.texcoord = { vrts[i].tu, vrts[i].tv };

				mVertices.push_back(temp);
				mIndices.push_back(i);
			}

			mVerCount = mVertices.size();
			mIndCount = mIndices.size();



			mLoaded = createBuffers();
			
			return mLoaded;
		}
		//==============================================================================================
		bool D3D11Mesh::loadMeshFromObj(string filePath){
			if (mLoaded)
				return false;

			// Очистка данных
			mVerCount = 0;
			mIndCount = 0;

			//Создание временного хранилища входящих данных, как только данные будут
			//загружены в подходящий формат скопируем эти данные в вершинный и индексный буферы
			XMFLOAT3 * Positions = (XMFLOAT3*)malloc(buffermax*sizeof(XMFLOAT3));
			XMFLOAT2 * TexCoords = (XMFLOAT2*)malloc(buffermax*sizeof(XMFLOAT2));
			XMFLOAT3 * Normals = (XMFLOAT3*)malloc(buffermax*sizeof(XMFLOAT3));

			// Индексы для массивов
			int PositionsI = 0;
			int TexCoordsI = 0;
			int NormalsI = 0;


			WCHAR strCommand[256] = { 0 };
			wifstream InFile(filePath.c_str());

			if (!InFile) {
				INFO("D3D11Mesh: No such file exists")
				return false;
			}





			while (InFile)
			{
				InFile >> strCommand;

				if (0 == wcscmp(strCommand, L"#"))
				{
					// Комментарий
				}
				else if (0 == wcscmp(strCommand, L"v"))
				{
					// Координаты
					float x, y, z;
					InFile >> x >> y >> z; float c = 0.1f;
					Positions[PositionsI++] = XMFLOAT3(x*c, y*c, z*c);
				}
				else if (0 == wcscmp(strCommand, L"vt"))
				{
					// Текстурные координаты
					float u, v;
					InFile >> u >> v;
					TexCoords[TexCoordsI++] = XMFLOAT2(u, -v);
				}
				else if (0 == wcscmp(strCommand, L"vn"))
				{
					// Нормали
					float x, y, z;
					InFile >> x >> y >> z;
					Normals[NormalsI++] = XMFLOAT3(x, y, z);
				}
				else if (0 == wcscmp(strCommand, L"f"))
				{
					// Face
					UINT iPosition, iTexCoord, iNormal;
					D3D11MeshVertex vertex;

					for (UINT iFace = 0; iFace < 3; iFace++)
					{
						ZeroMemory(&vertex, sizeof(D3D11MeshVertex));

						// OBJ формат использует массивы с индексами от 1
						InFile >> iPosition;
						vertex.position = Positions[iPosition - 1];

						if ('/' == InFile.peek())
						{
							InFile.ignore();

							if ('/' != InFile.peek())
							{
								// Опционно текстурные координаты
								InFile >> iTexCoord;
								vertex.texcoord = TexCoords[iTexCoord - 1];
							}

							if ('/' == InFile.peek())
							{
								InFile.ignore();

								// Опционно нормали
								InFile >> iNormal;
								vertex.normal = Normals[iNormal - 1];
							}
						}




						int res = -1;
						//Поиск существующей вершины
						for (int i = 0; i < mVerCount; i++)
							if (memcmp(&mVertices[i], &vertex, sizeof(D3D11MeshVertex)) == 0) 
								res = i;
						//Добавление
						if (res < 0){
							mVerCount++;
							mVertices.push_back(vertex); 
							res = mVerCount - 1;
						}
						mIndCount++;
						mIndices.push_back(res);

					}
				}
			}
			InFile.close();

			//Очистка временных массивов
			free(Positions);
			free(TexCoords);
			free(Normals);

			if (mVertices.size() == 0){
				INFO("CD3D11Mesh: Failed to read vertices from file")
				mLoaded = false;
			}
			else
				mLoaded = createBuffers();


			return mLoaded;
		}
		//==============================================================================================
		//==============================================================================================
		void D3D11Mesh::renderMesh(){
			//Запоминаем старые настройки рендерера
			ID3D11DepthStencilState* depthStencil = mRenderSystem->mCurrentDSState;
			XMFLOAT4X4 matProj = mRenderSystem->mCurrMatProj;
			XMFLOAT4X4 matView = mRenderSystem->mCurrMatView;

			//Работаем с флагами
			if (mNoDepth)
				mRenderSystem->mDeviceContext->OMSetDepthStencilState(mRenderSystem->mDepthStencilState2D, 1);			
			else 
				mRenderSystem->mDeviceContext->OMSetDepthStencilState(mRenderSystem->mDepthStencilState3D, 1);
			

			if (mOrthoProj)
				mRenderSystem->mCurrMatProj = mRenderSystem->mMatProj2D;
			else 
				mRenderSystem->mCurrMatProj = mRenderSystem->mMatProj3D;

			if (mNotMoving)
				XMStoreFloat4x4(&mRenderSystem->mCurrMatView, XMMatrixIdentity());




			mRenderSystem->reloadShader();







			UINT stride = sizeof(D3D11MeshVertex);
			UINT offset = 0;
			mRenderSystem->mDeviceContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
			mRenderSystem->mDeviceContext->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);


			mRenderSystem->mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			mRenderSystem->mDeviceContext->PSSetShaderResources(0, 1, &mTextureView);
			mRenderSystem->mDeviceContext->PSSetSamplers(0, 1, &mTexSamplerState);



			mRenderSystem->mDeviceContext->DrawIndexed(mIndCount, 0, 0);



			//Возвращаем старые настройки рендера
			mRenderSystem->mDeviceContext->OMSetDepthStencilState(depthStencil, 1);
			mRenderSystem->mCurrMatProj = matProj;
			mRenderSystem->mCurrMatView = matView;

		}
		//==============================================================================================
	}
}