#include <SimpleMath.h>
#include "Stage.h"
#include "LandShape.h"
#include "Marker.h"
#include "CollisionNode.h"
#include "Debug.h"
#include "Culling.h"
#include "GameManager.h"
#include "Event.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX::SimpleMath;

bool Stage::clearFlag_ = false;

Stage::Stage()
{
}

Stage::~Stage()
{
}

void Stage::Initialize()
{
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
	landShape.scale_ = Vector3(80.0f, 1.0f, 80.0f);
	landShape.box_.Initialize();
	landShape.mldName_ = L"Resources\\MDL\\Floor.MDL";
	landShape.cmoName_ = L"Resources\\cModels\\Floor.cmo";
	landShapeTable.push_back(landShape);

	int landArray[8][8] =
	{
		{ 0,0,0,0,0,0,0,0 },
		{ 0,1,1,1,0,0,1,0 },
		{ 0,1,0,1,0,0,1,0 },
		{ 0,1,1,1,1,1,1,0 },
		{ 0,1,0,0,0,0,1,0 },
		{ 0,1,0,1,1,1,1,0 },
		{ 0,1,0,1,1,0,1,0 },
		{ 0,1,0,0,0,0,0,0 }
	};

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (landArray[i][j] == 1) continue;
			landShape.trans_ = Vector3(j * 10.0f - 40 + 5, 0.0f, i * 10.0f - 40 + 5);
			landShape.rotate_ = Vector3(0.0f, 0.0f, 0.0f);
			landShape.scale_ = Vector3(10.0f, 10.0f, 10.0f);
			landShape.box_.Initialize();
			landShape.mldName_ = L"Resources\\MDL\\Box.MDL";
			landShape.cmoName_ = L"Resources\\cModels\\Box.cmo";
			landShapeTable.push_back(landShape);
		}
	}

	landShape.trans_ = Vector3(-25.0f, 0.0f, 39.0f);
	landShape.rotate_ = Vector3(0.0f, 0.0f, 0.0f);
	landShape.scale_ = Vector3(10.0f, 10.0f, 2.0f);
	landShape.box_.Initialize();
	landShape.mldName_ = L"Resources\\MDL\\Box.MDL";
	landShape.cmoName_ = L"Resources\\cModels\\Box.cmo";
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

	clearFlag_ = false;

	marker_.reset(new Marker);
	marker_->Initialize();
	Vector3 pos(-5.0f, 0.5f, 25.0f);
	marker_->SetPosition(pos);
	startPos_ = Vector3(-25.0f, 0.0f, 35.0f);
	landShape.box_.Initialize();

	clearEvent_.reset(new ClearEvent);
	clearEvent_->Initialize();
	clearEvent_->SetPosition(Vector3(-25.0f, 0.0f, 35.0f));
	clearEvent_->SetScale(Vector3(10.0f, 10.0f, 10.0f));

	Box box;
	box.Initialize();
	clearEvent_->SetBox(box);
	CollisionManager::GetInstance()->Entry(clearEvent_.get());
}

void Stage::Update()
{
	if (g_keyTracker->IsKeyPressed(DirectX::Keyboard::Q))
	{
		Debug::SwitchFlag();
	}

	for (auto it = landshapeList_.begin(); it != landshapeList_.end(); it++)
	{
		(*it)->Update();
	}
	marker_->Update();
}

void Stage::Render()
{
	for (auto it = landshapeList_.begin(); it != landshapeList_.end(); it++)
	{
		if (!*it) continue;

		(*it)->Calc();

		//if (Culling::InView((*it)->GetBox(), GameManager::GetInstance()->GetCamera(), 1))
			(*it)->Draw();
	}

	marker_->Render();

	wchar_t flag[20];
	if (clearFlag_)
		swprintf_s(flag, 20, L"ClearFlag = true");
	else
		swprintf_s(flag, 20, L"ClearFlag = false");
	g_spriteFont->DrawString(g_spriteBatch.get(), flag, Vector2(0, 60));
}

void Stage::Finalize()
{
}
