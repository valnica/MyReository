#pragma once

#include "DirectXTK.h"
#include <SimpleMath.h>
//#include "Character.h"
#include "State.h"

class Player;

class Camera
{
private:
	//カメラの位置
	DirectX::SimpleMath::Vector3 eye_;

	//注視点
	DirectX::SimpleMath::Vector3 target_;

	//カメラの上の方向
	DirectX::SimpleMath::Vector3 up_;

	//ビュー行列
	DirectX::SimpleMath::Matrix view_;

	//プロジェクション行列
	DirectX::SimpleMath::Matrix proj_;

	//視野角
	float fovY_;

	//アスペクト比
	float aspect_;

	//描画する最短の距離
	float near_;

	//描画する最長の距離
	float far_;

public:
	Camera(float Window_h,float Window_w);

	virtual ~Camera();

	void Update();

	void SetFovY(float fov);
	void SetAspect(float w, float h);
	void SetNear(float nearPos);
	void SetFar(float farPos);
	void SetEye(const DirectX::SimpleMath::Vector3 pos) { eye_ = pos; }
	void SetTarget(const DirectX::SimpleMath::Vector3 pos) { target_ = pos; }
	void SetUp(const DirectX::SimpleMath::Vector3 pos) { up_ = pos; }
	const DirectX::SimpleMath::Vector3& GetEye() const { return eye_; }
	const DirectX::SimpleMath::Vector3& GetTarget() const { return target_; }
	const DirectX::SimpleMath::Vector3& GetUp() const { return up_; }
	const DirectX::SimpleMath::Matrix& GetView() const { return view_; }
	const DirectX::SimpleMath::Matrix& GetProj() const { return proj_; }
};

class CameraState;

class CameraController
{
private:
	State<Camera>* state_;
	Camera* camera_;

public:

	CameraController();
	~CameraController();

	void Initialize(Camera* camera);
	void Update();

	void SetCamera(Camera* camera);

	Camera* GetCamera() { return camera_; }
};