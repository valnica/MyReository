//////////////////////////////////////////////
// Name : Camera
//
// Author : 山田 聖弥
//
// Date : 2017/1/9
//////////////////////////////////////////////
#pragma once

#include "DirectXTK.h"
#include <SimpleMath.h>
#include "State.h"
#include <memory>

namespace Math = DirectX::SimpleMath;

class Character;
class Player;

//////////////////////////////////////////////
// Class Name : Camera
//
// Over View : カメラ
//////////////////////////////////////////////
class Camera
{
private:
	//メインカメラ
	static std::weak_ptr<Camera> main_;

	//カメラの位置
	Math::Vector3 eye_;

	//注視点
	Math::Vector3 ref_;

	//カメラの上の方向
	Math::Vector3 up_;

	//ビュー行列
	Math::Matrix view_;

	//プロジェクション行列
	Math::Matrix proj_;

	//視野角
	float fovY_;

	//アスペクト比
	float aspect_;

	//描画する最短の距離
	float near_;

	//描画する最長の距離
	float far_;

	//ターゲットとなるキャラ
	std::weak_ptr<Player> target_;

public:
	Camera(float Window_h,float Window_w);
	virtual ~Camera();

	void Update();

	//注視点にするキャラクターの設定
	void SetTarget(std::shared_ptr<Player> target) { target_ = target; }
	//注視点にしているキャラクターの取得
	std::weak_ptr<Player> GetTarget() { return target_; }
	//メインカメラの設定
	static void MainCamera(std::shared_ptr<Camera> camera) { main_ = camera; }
	//メインカメラの取得
	static std::weak_ptr<Camera> MainCamera() { return main_; }

	//カメラの設定
	void SetFovY(float fov);
	void SetAspect(float w, float h);
	void SetNear(float nearPos);
	void SetFar(float farPos);
	void SetEye(const Math::Vector3 pos) { eye_ = pos; }
	void SetRef(const Math::Vector3 pos) { ref_ = pos; }
	void SetUp(const Math::Vector3 pos) { up_ = pos; }
	
	//カメラの情報の取得
	const Math::Vector3& GetEye() const { return eye_; }
	const Math::Vector3& GetRef() const { return ref_; }
	const Math::Vector3& GetUp() const { return up_; }
	const Math::Matrix& GetView() const { return view_; }
	const Math::Matrix& GetProj() const { return proj_; }
};

class CameraState;

//////////////////////////////////////////////
// Class Name : CameraController
//
// Over View : カメラを操作するためのクラス
//////////////////////////////////////////////
class CameraController
{
private:
	//カメラのstate
	std::weak_ptr<State<Camera>> state_;

	//カメラ
	std::weak_ptr<Camera> camera_;

public:
	CameraController();
	~CameraController();

	void Initialize(std::shared_ptr<Camera> camera);
	void Update();

	//カメラの設定
	void SetCamera(std::shared_ptr<Camera> camera);
};