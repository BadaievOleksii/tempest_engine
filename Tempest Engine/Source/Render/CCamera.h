#pragma once


#include "Core\TempestSharedHeader.h"


namespace Tempest {
	namespace Render {

		enum CoordAxis { AXIS_X, AXIS_Y, AXIS_Z };

		//Standart speed for camera moving
		const f32 CAMERA_MOVE = 0.2f;
		//Standart speed for camera rotation
		const f32 CAMERA_ROTATE = 0.03f;


		class Camera {
			friend class D3D11RenderSystem;

		private:



			//Current view matrix
			D3DXMATRIX mViewMat;


			//Do view matrix needs to be updated
			bool mNeedUpdate;

			//Rotation quaternion
			D3DXQUATERNION mCurrRot;
			//Eye vector e.g. position of the camera
			D3DXVECTOR3 mCurrPos;

			//Moving step for camera
			//X - strafe, Y - up-down, Z - forward-backward
			D3DXVECTOR3 mMove;
			//Rotating step for camera
			//X - around OX, Y - around OY, Z - around OZ
			D3DXVECTOR3 mRotate;

			/////// Variables for smooth moving
			//Interpolated view matrix
			D3DXMATRIX mSmoothView;
			D3DXQUATERNION mPrevRot;
			D3DXVECTOR3 mPrevPos;


			//Gets current representation of the specified coordinate axis
			D3DXVECTOR3 getAxis(CoordAxis);
		public:

			Camera();
			~Camera();

			//Sets camera to default position
			void resetCam();
			//Updates view matrix if flagged to
			void updateCam();

			void forwardCam(f32 = CAMERA_MOVE);
			void strafeCam(f32 = CAMERA_MOVE);
			void upCam(f32 = CAMERA_MOVE);


			void rollCam(f32 = CAMERA_ROTATE);
			void yawCam(f32 = CAMERA_ROTATE);
			void pitchCam(f32 = CAMERA_ROTATE);

			//Sets position of the camera to the given
			void setPosition(D3DXVECTOR3);


			//Returns current view matrix 
			D3DXMATRIX* getViewMatrix();

			//Returns view matrix, calculated using interpolation
			D3DXMATRIX* getRenderViewMatrix(f32);

		};
	}
}