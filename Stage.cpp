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

Stage::Stage()
{
	marker_ = new Marker;
	clearEvent = new ClearEvent;
}

Stage::~Stage()
{
	if (marker_)
		delete marker_;

	if (clearEvent)
		delete clearEvent;

	auto landShape = landshapeList_.begin();
	while (landShape != landshapeList_.end())
	{
		if ((*landShape))
			delete *landShape;

		landShape = landshapeList_.erase(landShape);
	}
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
		LandShape* landShape = new LandShape;
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
	marker_->Initialize();
	Vector3 pos(-5.0f, 0.5f, 25.0f);
	marker_->SetPosition(pos);
	startPos_ = Vector3(-25.0f, 0.0f, 35.0f);
	landShape.box_.Initialize();

	clearEvent->Initialize(this);
	clearEvent->SetPosition(Vector3(-25.0f, 0.0f, 35.0f));
	clearEvent->SetScale(Vector3(10.0f, 10.0f, 10.0f));
	Box box;
	box.Initialize();
	clearEvent->SetBox(box);
	CollisionManager::GetInstance()->Entry(clearEvent);
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
