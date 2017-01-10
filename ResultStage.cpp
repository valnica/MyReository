//////////////////////////////////////////////
// Name : ResultStage
//
// Author : 山田 聖弥
//
// Date : 2017/1/10
//////////////////////////////////////////////
#include "ResultStage.h"
#include "LandShape.h"
#include "Marker.h"

#include <SimpleMath.h>

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX::SimpleMath;

//////////////////////////////////////////////
// Name : ResultStage
//
// Over View : コンストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
ResultStage::ResultStage()
{
}

//////////////////////////////////////////////
// Name : ~ResultStage
//
// Over View : デストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
ResultStage::~ResultStage()
{
}

//////////////////////////////////////////////
// Name : Initialize
//
// Over View : 初期化処理
//
// Argument : 無し
//
// Return :  無し
//////////////////////////////////////////////
void ResultStage::Initialize()
{
	//地形の設定
	struct LandShapeTable
	{
		Vector3 trans_;
		Vector3 rotate_;
		Vector3 scale_;
		wchar_t* mldName_;
		wchar_t* cmoName_;
		Box box_;
	};

	std::vector<LandShapeTable> landShapeTable;
	LandShapeTable landShape;

	landShape.trans_ = Vector3(0.0f, 0.0f, 0.0f);
	landShape.rotate_ = Vector3(0.0f, 0.0f, 0.0f);
	landShape.scale_ = Vector3(20.0f, 1.0f, 20.0f);
	landShape.box_.Initialize();
	landShape.mldName_ = L"Resources\\MDL\\Floor.MDL";
	landShape.cmoName_ = L"Resources\\cModels\\Floor.cmo";
	landShapeTable.push_back(landShape);

	landShape.trans_ = Vector3(-5.0f, 0.0f, 10.0f);
	landShape.rotate_ = Vector3(0.0f, 0.0f, 0.0f);
	landShape.scale_ = Vector3(10.0f, 10.0f, 10.0f);
	landShape.box_.Initialize();
	landShape.mldName_ = L"Resources\\MDL\\Wall.MDL";
	landShape.cmoName_ = L"Resources\\cModels\\Wall.cmo";
	landShapeTable.push_back(landShape);

	landShape.trans_ = Vector3(5.0f, 0.0f, 10.0f);
	landShape.rotate_ = Vector3(0.0f, 0.0f, 0.0f);
	landShape.scale_ = Vector3(10.0f, 10.0f, 10.0f);
	landShape.box_.Initialize();
	landShape.mldName_ = L"Resources\\MDL\\Wall.MDL";
	landShape.cmoName_ = L"Resources\\cModels\\Wall.cmo";
	landShapeTable.push_back(landShape);

	int numLandShapeTable = landShapeTable.size();
	landshapeList_.resize(numLandShapeTable);

	for (int i = 0; i < numLandShapeTable; i++)
	{
		LandShapeTable* table = &landShapeTable[i];
		std::shared_ptr<LandShape> landShape;
		landShape.reset(new LandShape);
		wchar_t* mdlName = nullptr;
		wchar_t* cmoName = nullptr;

		if (lstrcmpW(table->mldName_, L"") != 0) mdlName = table->mldName_;
		if (lstrcmpW(table->cmoName_, L"") != 0) cmoName = table->cmoName_;

		Vector3 rotate = table->rotate_;

		landShape->Initialize(mdlName, cmoName);
		landShape->SetTrans(table->trans_);
		landShape->SetRotate(rotate);
		landShape->SetScale(table->scale_);

		landShape->SetBox(table->box_);

		landshapeList_[i] = std::move(landShape);
	}

	//写真で取るオブジェクトの設定
	marker_.reset(new Marker);
	marker_->Initialize();
	marker_->SetPosition(Vector3(1.5f, 2.0f, 1.0f));
	marker_->SetRotate(Vector3(0.0f, 180.0f, 0.0f));
}

//////////////////////////////////////////////
// Name : Update
//
// Over View : 更新処理
//
// Argument : 無し
//
// Return :  無し
//////////////////////////////////////////////
void ResultStage::Update()
{
	//更新処理
	for (auto it = landshapeList_.begin(); it != landshapeList_.end(); it++)
	{
		(*it)->Update();
	}
	marker_->Update();
}

//////////////////////////////////////////////
// Name : Render
//
// Over View : 描画処理
//
// Argument : 無し
//
// Return :  無し
//////////////////////////////////////////////
void ResultStage::Render()
{
	//描画処理
	for (auto it = landshapeList_.begin(); it != landshapeList_.end(); it++)
	{
		(*it)->Calc();
		(*it)->Draw();
	}
	marker_->Render();
}

//////////////////////////////////////////////
// Name : Finalize
//
// Over View : 終了処理
//
// Argument : 無し
//
// Return :  無し
//////////////////////////////////////////////
void ResultStage::Finalize()
{
}
