#pragma once

#include "Core\TempestSharedHeader.h"
#include "Render\CMesh.h"

namespace Tempest {
	namespace Render {
		const int buffermax = 16384;
		struct D3D11MeshVertex
		{
			XMFLOAT3 position;
			XMFLOAT3 normal;
			XMFLOAT2 texcoord;
		};


		class D3D11Mesh : public Mesh {
			friend class D3D11RenderSystem;

		private:
			D3D11RenderSystem* mRenderSystem;

			ID3D11Buffer* mVertexBuffer;
			ID3D11Buffer* mIndexBuffer;

			ID3D11ShaderResourceView* mTextureView;
			ID3D11SamplerState* mTexSamplerState;
			ID3D11Texture2D* mTexture;

			//D3D11MeshVertex mVertices[buffermax];
			//DWORD  mIndices[buffermax];
			vector<D3D11MeshVertex> mVertices;
			vector<DWORD> mIndices;
			int	mVerCount;
			int mIndCount;

			





			bool createBuffers();
		public:
			




			D3D11Mesh(D3D11RenderSystem* renderSystem);
			~D3D11Mesh();

			bool loadMeshFromArray(vector<MeshVertex>);
			bool loadMeshFromObj(string filePath);


			void renderMesh();
		};
	}
}