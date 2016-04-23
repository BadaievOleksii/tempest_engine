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
		������ (��� � �����) � ����������� � ������������ ����������.

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
			//"�����" - ��������� ��������� ����
			bool mNoDepth;		//��� ���������� ������� � �������������� ������ ������ �� ������� �������
			bool mOrthoProj;	//2�-�������� - ��� ����, ����� ���������� ���� �������������
			bool mNotMoving;	//��� �������� ������ ��� �������� �� �����
			bool mBillboard;	//��� ������ �������� ����� � ������ *�� �������*




			virtual bool loadMeshFromArray(vector<MeshVertex>) = 0;
			virtual bool loadMeshFromObj(string filePath) = 0;
			void setMaterial(Material*);

			virtual void renderMesh() = 0;
		};
	}
}