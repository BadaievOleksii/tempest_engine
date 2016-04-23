#pragma once

#include "Core\TempestSharedHeader.h"

namespace Tempest {
	namespace Render {

		struct MeshVertex
		{
			f32 x, y, z; //Coords in space
			f32 tu, tv; //Texture coordinates
		};

		
		/*
		Модель (или её часть) с собственным и единственным материалом.

		*/
		class Mesh {
			friend class D3D9RenderSystem;
			friend class D3D11RenderSystem;

		private:

		protected:
			vector<MeshVertex> mVertices;
			DWORD* mIndexes;
			Material* mMaterial;
			bool mLoaded;

			Mesh();
			virtual ~Mesh();

		public:
			//"Флаги" - особенное поведение меша
			bool mNoDepth;		//Меш игнорирует глубину и отрисовывается просто исходя из порядка рендера
			bool mOrthoProj;	//2Д-проекция - для того, чтобы координаты были попиксельными
			bool mNotMoving;	//При движении камеры меш остается на месте
			bool mBillboard;	//Меш всегда повернут лицом к камере *НЕ СДЕЛАНО*




			virtual bool loadMeshFromArray(vector<MeshVertex>) = 0;
			virtual bool loadMeshFromObj(string filePath) = 0;
			void setMaterial(Material*);

			virtual void renderMesh() = 0;
		};
	}
}