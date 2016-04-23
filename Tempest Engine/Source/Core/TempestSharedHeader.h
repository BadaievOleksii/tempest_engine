#pragma once

#include "resource.h"

#include "TempestStdIncludes.h"
#include "TempestTypes.h"
#include "TempestLogging.h"


#ifdef _DEBUG

//To-remove
#define ENGINE_NAME "NERVUS"

#define TEST_PIC "F:\\Games\\Programming\\Project\\Media\\34672_cards.jpg"
#define BMP_PIC "F:\\Games\\Programming\\Project\\Media\\405651.bmp"

#define DEFAULT_TEXTURE "F:\\Games\\Programming\\Project\\My code\\Nervus\\neuron.png"


#endif



//Predeclarations
namespace Tempest{
	namespace Core{
		class TempestCore;
		class Window;
		class Input;
		class Chrono;


	}
	namespace Render{
		class RenderSystem;
		class D3D11RenderSystem;
		class D3D11Mesh;
		class Camera;
		class Mesh;
		class Texture;
		class Material;

	}
}



namespace Tempest {
	namespace Render {
		enum RENDERSYSTEM_TYPE { RS_EMPTY, RS_D3D9, RS_D3D11, RS_OPENGL };
	}
}