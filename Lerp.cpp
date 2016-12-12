////////////////////////////////////////////////////////////////////////////////
/// @file Lerp.cpp
/// 線形補間関連クラス
///
/// @author  Takafumi Murase @ freeplay inc.
///
/// @version Ver1.00 date2012.06.06  初版
///
/// @since   2012.06.06
///
///  Copyright(c) TRIDENT college 2012 , Takafumi Murase All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////
#include "Lerp.h"
#include <SimpleMath.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;


////////////////////////////////////////////////////////////////////////////////
/// @brief カーブ通過点の情報
////////////////////////////////////////////////////////////////////////////////
class LerpInfo
{
public:
	float time;
	float x, y, z;
};

class ILerpDebugData
{
public:
	// 先頭データの取得
	LerpInfo* GetStart();

	// 最終データを取得
	LerpInfo* GetEnd();

};

////////////////////////////////////////////////////////////////////////////////
/// @brief カーブ通過点のコンテナ
////////////////////////////////////////////////////////////////////////////////
class LerpData : public ILerpData
{
public:
	LerpData();
	virtual ~LerpData();

	// データリセット
	void Reset();

	// 先頭データの取得
	LerpInfo* GetStart();

	// 最終データを取得
	LerpInfo* GetEnd();

	// データの数を取得
	size_t GetCount() override;

	// データを追加する
	void Add(float time, float x, float y, float z) override;

	// 追加されているデータを変更
	void SetData(unsigned int n, float time, float x, float y, float z) override;

	// 追加されているデータの座標を変更
	void ChangePos(unsigned int n, float x, float y, float z) override;

	// 始点から終点までの通過時間を最適化する
	void ComputeConstant() override;

	const float* GetPosition(unsigned int num) override;

	const static unsigned int num = 100;
	LerpInfo data[num];
	unsigned int count;

};


//-----------------------------------------------------------------------------
// カーブ情報コンテナクラス
//-----------------------------------------------------------------------------

LerpData::LerpData()
{
	count = 0;
}

LerpData::~LerpData()
{
}

// データリセット
void LerpData::Reset()
{
	count = 0;
}

// 先頭データの取得
LerpInfo* LerpData::GetStart()
{
	if (count == 0) return nullptr;
	return &data[0];
}

// 最終データを取得
LerpInfo* LerpData::GetEnd()
{
	if (count == 0) return nullptr;
	return &data[count - 1];
}

// データの数を取得
size_t LerpData::GetCount()
{
	return count;
}

// データを追加する
void LerpData::Add(float time, float x, float y, float z)
{
	if (count >= num) return;

	SetData(count, time, x, y, z);

	count++;
}

// 追加されているデータを変更
void LerpData::SetData(unsigned int n, float time, float x, float y, float z)
{
	if (n >= num) return;

	if (n == 0 && time != 0.0f) time = 0.0f;
	auto &d = data[n];
	d.time = time;
	d.x = x;
	d.y = y;
	d.z = z;

}

// 追加されているデータの座標を変更
void LerpData::ChangePos(unsigned int n, float x, float y, float z)
{
	if (n >= num) return;
	auto &d = data[n];
	d.x = x;
	d.y = y;
	d.z = z;
}


// 補間を等速移動にする
void LerpData::ComputeConstant()
{

	// 登録数が２つ未満の場合何もしない
	if (count < 2) return;

	// 区間ごとの長さを登録する場所
	float len_table[num];

	// 終了時間を取得する
	float end_time = data[count - 1].time;

	// 全体の長さ
	float len = 0.0f;

	// 区間の数繰り返す
	for (unsigned int i = 0; i < count - 1; i++)
	{
		// 区間の距離と、全体の距離を求める
		float x = data[i + 1].x - data[i].x;
		float y = data[i + 1].y - data[i].y;
		float z = data[i + 1].z - data[i].z;

		// 区間の距離
		len_table[i] = sqrt(x*x + y*y + z*z);

		// 全体の距離
		len += len_table[i];
	}

	// 区間の数繰り返す
	for (unsigned int i = 0; i < count - 1; i++)
	{
		// 区間の通過時間を、区間の距離で割り当てる
		data[i + 1].time = data[i].time + end_time * (len_table[i] / len);
	}
}

const float* LerpData::GetPosition(unsigned int num)
{
	if (num >= count) return nullptr;
	return &data[num].x;
}


//-----------------------------------------------------------------------------
// 処理クラス
//-----------------------------------------------------------------------------
class Lerp::Impl
{
public:
	Impl() :
		data(nullptr),
		x(0), y(0), z(0), w(1),
		elapsed(1),
		total_time(0),
		time(0),
		count(0),
		end_time(0),
		looptype(STOP),
		world(Matrix::Identity)
	{};
	~Impl(){};

	std::shared_ptr<LerpData> data;  // データ

	float elapsed;	   // 経過時間
	float total_time;  // 経過時間
	float time;        // １回の経過時間
	float end_time;    // １回の終了時間
	int count;         // 繰り返し回数
	LoopType looptype; // 繰り返しのタイプ
	Matrix world;

	union // 結果の座標
	{
		struct
		{
			float x, y, z, w;
		};
		float vec[4];
	};

	void SetData(std::shared_ptr<LerpData> &s)
	{

		if (s == nullptr) return;
		if (s->GetCount() == 0) return;
		data = s;
		LerpInfo *start = data->GetStart();
		LerpInfo *end = data->GetEnd();
		if (start == nullptr || end == nullptr) return;

		// 終了時間
		end_time = end->time;

		// 時間のリセット
		total_time = 0;
		time = 0;
		count = 0;

		// 開始座標
		x = start->x;
		y = start->y;
		z = start->z;
	}

	// 時間を戻して、座標を開始位置にする
	void Reset()
	{
		total_time = 0;
		time = 0;
		count = 0;

		LerpInfo *start = data->GetStart();
		x = start->x;
		y = start->y;
		z = start->z;

	}

	// 時間を変更
	void ChangeTime(float t)
	{
		total_time = t;
		float e = elapsed;
		elapsed = 0.0f;
		Update();
		elapsed = e;
	}


	bool IsEmpty() const
	{
		if (data == nullptr) return true;
		if (data->GetCount() == 0) return true;

		return false;
	}

	// 必要な時間情報を求める
	void ClipTime()
	{
		count = (int)(fabs(total_time) / end_time);
		time = total_time - (end_time * count);
	}



	// 補間情報を更新する
	void Update()
	{
		if (IsEmpty()) return;
		//----------------------------------------
		// 補間に必要な時間を求める処理

		// 時間を進める
		total_time += elapsed;
		if (total_time < 0.0f) total_time = 0.0f;

		// データが設定されていないとき
		if (data == nullptr) return;

		// 時間情報を求める
		ClipTime();

		//----------------------------------------
		// 補間に使う情報を求める処理

		// データの先頭と終端を求める
		LerpInfo *start = data->GetStart();
		LerpInfo *end = data->GetEnd();

		// データが設定されていないとき
		if (start == nullptr || end == nullptr) return;

		// 現在の時間から、使われているデータを探す
		LerpInfo *target = start;
		for (; target != end + 1; target++)
		{
			if (target->time > time)break;
		}

		// 現在使われているデータの、開始と終了のポインタを求める
		LerpInfo *s = target - 1;
		LerpInfo *e = target;

		//----------------------------------------
		// 補間に使う係数求める処理

		// 時間から係数（0.0～1.0）を求める
		float t = (time - s->time) / (e->time - s->time); // 係数を求める

		//----------------------------------------
		// 繰り返しのときの差（オフセット）を求める

		// オフセット座標
		float ox, oy, oz;

		// オフセット座標を求める
		switch (looptype)
		{
		case STOP:
			if (count > 0)
			{
				// 補間処理をせず、終点の座標を結果とする
				x = end->x;
				y = end->y;
				z = end->z;
				return;
			}
			// オフセット座標なし	
			ox = oy = oz = 0;
			break;
		case LOOP:
			// オフセット座標なし
			ox = oy = oz = 0;
			break;
		case STRIP:
			// オフセット座標を求める
			ox = (end->x - start->x) * count;
			oy = (end->y - start->y) * count;
			oz = (end->z - start->z) * count;
			break;
		}


		//----------------------------------------
		// 補間の計算をして、座標を求める
		{

			// 次の数式に基づいて線形補間を行います。x + s(y - x)
			x = s->x + t * (e->x - s->x);
			y = s->y + t * (e->y - s->y);
			z = s->z + t * (e->z - s->z);
		}

		//----------------------------------------
		// オフセットを加える
		x += ox;
		y += oy;
		z += oz;


		Vector3 pos = Vector3::Transform(Vector3(vec), world);

		x = pos.x;
		y = pos.y;
		z = pos.z;
	}

	// 補間が終了（停止）しているか
	bool IsStop()
	{
		if (looptype == STOP && end_time < total_time) return true;

		return  false;
	}

};


Lerp::Lerp(void) : pImpl(std::make_shared<Impl>())
{
}

Lerp::Lerp(DataPtr & s) : Lerp()
{
	pImpl->SetData(std::dynamic_pointer_cast<LerpData>(s));
}


Lerp::~Lerp(void)
{
}

// 繰り返しのタイプの設定
void Lerp::SetLoop(LoopType type)
{
	pImpl->looptype = type;
}

// 補間で使うデータを設定する
void Lerp::SetData(DataPtr &s)
{
	pImpl->SetData(std::dynamic_pointer_cast<LerpData>(s));
}


// 時間を戻して、座標を開始位置にする
void Lerp::Reset()
{
	pImpl->Reset();
}

// 経過時間の設定
void Lerp::SetElapsedTime(float e)
{
	pImpl->elapsed = e;
}

// 時間を変更
void Lerp::ChangeTime(float t)
{
	pImpl->ChangeTime(t);
}


bool Lerp::IsEmpty() const
{
	return pImpl->IsEmpty();
}

// 補間情報を更新する
void Lerp::Update()
{
	pImpl->Update();
}

// 補間が終了（停止）しているか
bool Lerp::IsStop() const
{
	return pImpl->IsStop();
}

// 繰り返し回数を求める
int Lerp::GetCount() const
{
	return pImpl->count;
}


// Xの取得
const float& Lerp::GetX() const
{
	return pImpl->x;
}

// Yの取得
const float& Lerp::GetY() const
{
	return pImpl->y;
}

// Zの取得
const float& Lerp::GetZ() const
{
	return pImpl->z;
}

// 結果をfloat[4]で取得
const float* Lerp::GetResult() const
{
	return pImpl->vec;
}

// 結果をfloat[4]で取得
Lerp::operator const float*() const
{
	return pImpl->vec;
}

const float & Lerp::operator[](int num) const
{
#ifdef _DEBUG
	// 0,1,2,3で指定してください
	if (num < 0 || num > 3) //throw std::out_of_range("range of 0-3");
#endif // _DEBUG
	return pImpl->vec[num];
}

const float & Lerp::operator[](char dimension) const
{
#ifdef _DEBUG
	// 'X','Y','Z','W'で指定してください
	if (dimension < 'X' || dimension > 'W') //throw std::out_of_range("range of 'X'-'Z'");
#endif // _DEBUG
	return pImpl->vec[dimension - 'X'];
}


Lerp::DataPtr Lerp::CreateData()
{
	return std::make_shared<LerpData>();
}

Lerp* Lerp::Clone() const
{
	auto clone = new Lerp();

	clone->pImpl.reset(new Impl(*pImpl.get()));

	return clone;
}

Lerp::DataPtr Lerp::GetData() const
{
	return pImpl->data;
}

// ワールドの設定
void Lerp::SetWorld(const XMFLOAT4X4& world)
{
	pImpl->world = world;
}

// ワールドの取得
const XMFLOAT4X4& Lerp::GetWorld() const
{
	return pImpl->world;
}



// ループタイプ取得
Lerp::LoopType Lerp::GetLoopType() const
{
	return pImpl->looptype;
}