#include "CMesh.h"

#include "Render\CRenderSystem.h"
#include "Render\CMaterial.h"

namespace Tempest {
	namespace Render {
		Mesh::Mesh()  
			: mMaterial(nullptr), mLoaded(false), mNoDepth(false), mOrthoProj(false), mNotMoving(false), mBillboard(false)
		{

		}
		//----------------------------------------------------------------------------------
		Mesh::~Mesh(){

		}
		//----------------------------------------------------------------------------------
		//----------------------------------------------------------------------------------
		void Mesh::setMaterial(Material* mat){
			mMaterial = mat;
		}
		//----------------------------------------------------------------------------------

	}
}