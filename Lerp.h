////////////////////////////////////////////////////////////////////////////////
/// @file Lerp.h
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
#pragma once
#include <memory>
#include <DirectXMath.h>

////////////////////////////////////////////////////////////////////////////////
/// @brief 線形補間データクラス
////////////////////////////////////////////////////////////////////////////////
class ILerpData
{
public:
	// コンストラクタ
	ILerpData(){};

	// デストラクタ
	virtual ~ILerpData(){};

	// データをリセット
	virtual void Reset() = 0;

	// データの個数を取得
	virtual size_t GetCount() = 0;

	// データを追加する
	virtual void Add(float time, float x, float y, float z) = 0;

	// 既存のデータをすべてを変更する
	virtual void SetData(unsigned int n, float time, float x, float y, float z) = 0;

	// 既存のデータを変更する
	virtual void ChangePos(unsigned int n, float x, float y, float z) = 0;

	// 時間を均等に設定する
	virtual void ComputeConstant() = 0;

	// データを取得する
	virtual const float* GetPosition(unsigned int num) = 0;
};


////////////////////////////////////////////////////////////////////////////////
/// @brief 線形補間演算クラス
////////////////////////////////////////////////////////////////////////////////
class Lerp
{
public:
	// 繰り返しのタイプの型
	enum LoopType
	{
		STOP,  // 最後の座標で停止
		LOOP,  // 最初の座標に戻り繰り返す
		STRIP  // 最後の座標から継続
	};
public:
	// 結果をX,Y,Zをそれぞれ受け取る
	const float& GetX() const;
	const float& GetY() const;
	const float& GetZ() const;

	// 結果をfloat[4]で受け取る
	const float* GetResult() const;

	// 結果をfloat[4]で受け取る
	operator const float*() const;
	const float& operator[](int num) const;
	const float& operator[](char dimension) const;

//	typedef std::shared_ptr<ILerpData> DataPtr;
	using DataPtr = std::shared_ptr < ILerpData > ;

	// コンストラクタ
	Lerp(void);
	Lerp(DataPtr &s);

	// デストラクタ
	virtual ~Lerp(void);

	// 繰り返しのタイプの設定
	void SetLoop(LoopType type);

	// 補間で使うデータを設定する
	void SetData(DataPtr &s);

	// 時間を戻して、座標を開始位置にする
	void Reset();

	// 経過時間の設定
	void SetElapsedTime(float e);

	// 時間を変更
	void ChangeTime(float t);

	// データが空かチェックする
	bool IsEmpty() const;

	// 補間情報を更新する
	void Update();

	// 補間が終了（停止）しているか
	bool IsStop() const;

	// 繰り返し回数を求める
	int GetCount() const;

	// データの作成
	static DataPtr CreateData();

	//---------------------------
	// DirectXTK依存処理
	// ワールドの設定
	void SetWorld(const DirectX::XMFLOAT4X4& world);

	// ワールドの取得
	const DirectX::XMFLOAT4X4& GetWorld() const;
	//---------------------------

	//---------------------------
	// デバッグ用
	// データのクローンを作成
	Lerp* Clone() const;

	// データの取得
	DataPtr GetData() const;

	// ループタイプの取得
	LoopType GetLoopType() const;
	//---------------------------


private:
	class Impl; std::shared_ptr<Impl> pImpl;
};


