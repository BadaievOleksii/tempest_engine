#include "CCamera.h"

namespace Tempest {
	namespace Render {
		//==============================================================================================
		Camera::Camera(){
			resetCam();
		}
		//==============================================================================================
		Camera::~Camera(){
		}
		//==============================================================================================
		void Camera::resetCam(){
			mNeedUpdate = true;
			D3DXQuaternionIdentity(&mCurrRot);
			D3DXMatrixIdentity(&mViewMat);
			mCurrPos = D3DXVECTOR3(0.0f, 0.0f, -4.0f);

			D3DXQuaternionIdentity(&mPrevRot);
			mPrevPos = D3DXVECTOR3(0.0f, 0.0f, -4.0f);

			mMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			mRotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		//==============================================================================================
		void Camera::updateCam(){
			mPrevPos = mCurrPos;
			mPrevRot = mCurrRot;
			if (mNeedUpdate){

				//Moving camera using mMove as a step
				mCurrPos += getAxis(AXIS_X) * mMove.x;
				mCurrPos += getAxis(AXIS_Y) * mMove.y;
				mCurrPos += getAxis(AXIS_Z) * mMove.z;
				mMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


				//Rotating camera using mRotate as angles
				D3DXQUATERNION rotX, rotY, rotZ;
				D3DXQuaternionRotationAxis(&rotX,
					&getAxis(AXIS_X),
					mRotate.x);
				D3DXQuaternionRotationAxis(&rotY,
					&getAxis(AXIS_Y),
					mRotate.y);
				D3DXQuaternionRotationAxis(&rotZ,
					&getAxis(AXIS_Z),
					mRotate.z);

				mCurrRot *= rotX * rotY * rotZ;
				D3DXQuaternionNormalize(&mCurrRot, &mCurrRot);
				//mCurrRot *= rotY;
				//D3DXQuaternionNormalize(&mCurrRot, &mCurrRot);
				//mCurrRot *= rotZ;
				//D3DXQuaternionNormalize(&mCurrRot, &mCurrRot);
				mRotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				//Applying all transformations to view matrix
				D3DXMATRIX matTranslation;
				D3DXMatrixTranslation(&matTranslation,
					-mCurrPos.x,
					-mCurrPos.y,
					-mCurrPos.z);

				D3DXMATRIX matRotation;
				D3DXMatrixRotationQuaternion(&matRotation, &D3DXQUATERNION(-mCurrRot.x,
					-mCurrRot.y,
					-mCurrRot.z,
					mCurrRot.w));


				D3DXMatrixMultiply(&mViewMat, &matTranslation, &matRotation);
				mNeedUpdate = false;


			}
		}
		//==============================================================================================
		//==============================================================================================
		void Camera::pitchCam(f32 angle){
			//rotateCam(angle, axisX);
			mRotate.x += angle;
			mNeedUpdate = true;
		}
		//==============================================================================================
		void Camera::yawCam(f32 angle){
			//rotateCam(angle, axisY);
			mRotate.y += angle;
			mNeedUpdate = true;
		}
		//==============================================================================================
		void Camera::rollCam(f32 angle){
			//rotateCam(angle, axisZ);
			mRotate.z += angle;
			mNeedUpdate = true;
		}
		//==============================================================================================
		void Camera::strafeCam(f32 amount){
			//moveCam(amount, axisX);
			mMove.x += amount;
			mNeedUpdate = true;
		}
		//==============================================================================================
		void Camera::upCam(f32 amount){
			//moveCam(amount, axisY);
			mMove.y += amount;
			mNeedUpdate = true;
		}
		//==============================================================================================
		void Camera::forwardCam(f32 amount){
			//moveCam(amount, axisZ);
			mMove.z += amount;
			mNeedUpdate = true;
		}
		//==============================================================================================
		void Camera::setPosition(D3DXVECTOR3 newPos){
			mCurrPos = newPos;
			mNeedUpdate = true;
		}		
		//==============================================================================================
		D3DXVECTOR3 Camera::getAxis(CoordAxis cA){
			D3DXVECTOR3 vAxis;

			switch (cA){
			case AXIS_X:
				vAxis.x = mViewMat._11;
				vAxis.y = mViewMat._21;
				vAxis.z = mViewMat._31;
				break;
			case AXIS_Y:
				vAxis.x = mViewMat._12;
				vAxis.y = mViewMat._22;
				vAxis.z = mViewMat._32;
				break;
			case AXIS_Z:
				vAxis.x = mViewMat._13;
				vAxis.y = mViewMat._23;
				vAxis.z = mViewMat._33;
				break;
			}

			return vAxis;
		}
		//==============================================================================================
		//==============================================================================================
		D3DXMATRIX* Camera::getViewMatrix(){
			return &mViewMat;
		}
		//==============================================================================================
		D3DXMATRIX* Camera::getRenderViewMatrix(f32 interpolation){

			if (mPrevPos == mCurrPos && mPrevRot == mCurrRot) {
				return &mViewMat;
			}


			D3DXVECTOR3 interPos;
			D3DXQUATERNION interQuat;

			D3DXMATRIX intMatTrans, intMatRot;


			interPos = interpolation * mCurrPos + (1.0f - interpolation) * mPrevPos;

			D3DXMatrixTranslation(&intMatTrans,
				-interPos.x,
				-interPos.y,
				-interPos.z);


			interQuat = mPrevRot + interpolation*(mCurrRot - mPrevRot);
			D3DXQuaternionNormalize(&interQuat, &interQuat);
			D3DXMatrixRotationQuaternion(&intMatRot, &D3DXQUATERNION(-interQuat.x,
				-interQuat.y,
				-interQuat.z,
				interQuat.w));


			D3DXMatrixMultiply(&mSmoothView, &intMatTrans, &intMatRot);

			return &mSmoothView;
		}
		//==============================================================================================
	}
}