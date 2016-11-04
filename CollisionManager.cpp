#include "CollisionManager.h"
//#include "Player.h"
//#include "Enemy.h"

using namespace DirectX::SimpleMath;

void CollisionManager::Reset()
{
	player_.clear();
	enemy_.clear();
}

CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}

void CollisionManager::Initialize()
{
	player_.clear();
	enemy_.clear();
}

void CollisionManager::Update()
{
	//Collision collision;

	////各当たり判定を行う

	////プレイヤーの攻撃判定
	//for (auto playerIt = player_.begin(); playerIt != player_.end(); playerIt++)
	//{
	//	//攻撃力がなかったら処理をやめる
	//	if ((*playerIt)->GetPower() <= 0) continue;

	//	for (auto enemyIt = enemy_.begin(); enemyIt != enemy_.end(); enemyIt++)
	//	{
	//		auto playerWeaponCollisionBody = (*playerIt)->GetWeaponCollisionBody();
	//		auto enmeyCollisionBody = (*enemyIt)->GetCollisionBody();

	//		if (collision.CheckCapsule2Capsule(playerWeaponCollisionBody, enmeyCollisionBody))
	//		{
	//			(*enemyIt)->TakeDamage((*playerIt)->GetPower(),(*playerIt)->GetDelay());
	//		}
	//	}
	//}

	Reset();
}

void CollisionManager::Entry(Player * player)
{
	player_.push_back(player);
}

void CollisionManager::Entry(Enemy * enemy)
{
	enemy_.push_back(enemy);
}

CollisionManager * CollisionManager::GetInstance()
{
	static CollisionManager* instance_ = nullptr;

	if (!instance_)
		instance_ = new CollisionManager;

	return instance_;
}



// 最小値と最大値の間にクランプする
inline float Clamp(float _x, float _min, float _max)
{
	return min(max(_x, _min), _max);
}

//--------------------------------------------------------------------------------------------
// 説　明 : 点と線分の最近接点を計算
// 引　数 : _point	点
//			_segment	線分
//			_closest	最近接点(結果出力用）
// 戻り値 : なし
// メ　モ : 
//--------------------------------------------------------------------------------------------
void ClosestPtPoint2Segment(const Vector3& _point, const Segment& _segment, Vector3* _closest)
{
	Vector3 segv;
	Vector3 s2p;
	float t;

	segv = _segment.end_ - _segment.start_;
	s2p = _point - _segment.start_;
	t = segv.Dot(s2p) / segv.Dot(segv);

	// 線分の外側にある場合、tを最接近点までクランプ
	t = Clamp(t, 0, 1);

	// クランプされているtからの射影されている位置を計算
	*_closest = t * segv + _segment.start_;
}

//--------------------------------------------------------------------------------------------
// 説　明 : 線分と線分の最近接点を計算
// 引　数 : _segment0	線分0
//			_segment1	線分1
//			_closest0	線分0上の最近接点(結果出力用）
//			_closest1	線分1上の最近接点(結果出力用）
// 戻り値 : なし
// メ　モ : 
//--------------------------------------------------------------------------------------------
void ClosestPtSegment2Segment(const Segment& _segment0, const Segment& _segment1, Vector3* _closest0, Vector3* _closest1)
{
	const float epsilon = 1.0e-5f;	// 誤差吸収用の微小な値
	Vector3 d0, d1, r;
	float a, b, c, e, f;
	float s, t;
	float denom;
	float tnom;

	d0 = _segment0.end_ - _segment0.start_;		// 線分0の方向ベクトル
	d1 = _segment1.end_ - _segment1.start_;		// 線分1の方向ベクトル
	r = _segment0.start_ - _segment1.start_;	// 線分1の始点から線分0の始点へのベクトル
	a = d0.Dot(d0);	// 線分0の距離の二乗
	e = d1.Dot(d1);	// 線分1の距離の二乗
					//	b = d0.Dot(d1);	// 最適化の為後方に移動した
					//	c = d0.Dot(r);	// 最適化の為後方に移動した
					//	f = d1.Dot(r);	// 最適化の為後方に移動した

					// いづれかの線分の長さが0かどうかチェック
	if (a <= epsilon && e <= epsilon)
	{// 両方長さ0
		*_closest0 = _segment0.start_;
		*_closest1 = _segment1.start_;
		return;
	}

	if (a <= epsilon)
	{// 線分0が長さ0
		*_closest0 = _segment0.start_;
		ClosestPtPoint2Segment(_segment0.start_, _segment1, _closest1);
	}

	if (e <= epsilon)
	{// 線分1が長さ0
		*_closest1 = _segment1.start_;
		ClosestPtPoint2Segment(_segment1.start_, _segment0, _closest0);
	}

	b = d0.Dot(d1);
	f = d1.Dot(r);
	c = d0.Dot(r);

	denom = a * e - b * b;	// 常に非負
							// 線分が平行でない場合、直線0上の直線1に対する最近接点を計算、そして
							// 線分0上にクランプ。そうでない場合は任意のsを選択
	if (denom != 0)
	{
		s = Clamp((b * f - c * e) / denom, 0, 1);
	}
	else
	{
		s = 0;
	}

	// 直線1上の最接近点を計算
	tnom = b * s + f;

	if (tnom < 0)
	{
		t = 0;
		s = Clamp(-c / a, 0, 1);
	}
	else if (tnom > e)
	{
		t = 1;
		s = Clamp((b - c) / a, 0, 1);
	}
	else
	{
		t = tnom / e;
	}

	*_closest0 = s * d0 + _segment0.start_;
	*_closest1 = t * d1 + _segment1.start_;
}


bool Collision::CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB, Vector3* inter)
{
	Vector3 sub = sphereA.center_ - sphereB.center_;

	float lengthSqured = VectorLengthSquare(sub);

	float radius_sum = sphereA.radius_ + sphereB.radius_;
	float radius_sumSquared = radius_sum * radius_sum;

	if (lengthSqured > radius_sumSquared)
	{
		return false;
	}

	if (inter)
	{
		Vector3 Btointer = sub*sphereB.radius_ / (sphereA.radius_ + sphereB.radius_);
		*inter = Btointer + Btointer;
	}

	return true;
}

float Collision::VectorLengthSquare(DirectX::SimpleMath::Vector3 & v)
{
	float lenthSquared = v.LengthSquared();

	return lenthSquared;
}

float Collision::Distance3DSquared(const DirectX::SimpleMath::Vector3 & p1, const DirectX::SimpleMath::Vector3 & p2)
{
	float distance = p1.x * p2.x + p1.y*p2.y + p1.z * p2.z;

	return distance;
}

bool Collision::CheckCapsule2Capsule(const Capsule & capsule1, const Capsule & capsule2, Vector3* inter)
{
	float distanceSQ = GetSqDistanceSegment2Segment(capsule1.segment_, capsule2.segment_);

	float radisuSum = capsule1.radius_ + capsule2.radius_;
	float radiusSumSQ = radisuSum * radisuSum;

	if (distanceSQ > radiusSumSQ)
	{
		return false;
	}

	if (inter)
	{
		Vector3 pointA, pointB;
		ClosestPtSegment2Segment(capsule1.segment_, capsule2.segment_, &pointA, &pointB);
		Vector3 sub = pointA - pointB;
		Vector3 Btopoint = sub * capsule2.radius_ / (capsule1.radius_ + capsule2.radius_);

		*inter = pointB + Btopoint;
	}

	return true;
}

bool Collision::CheckSphere2Capsule(const Sphere & sphere, const Capsule & capsule,Vector3* inter)
{
	float distanceSQ = GetSqDistancePoint2Segment(sphere.center_, capsule.segment_);

	float radiusSum = sphere.radius_ + capsule.radius_;
	float radiusSumSQ = radiusSum * radiusSum;

	if (distanceSQ > radiusSumSQ)
	{
		return false;
	}

	if (inter)
	{
		Vector3 point;
		ClosestPtPoint2Segment(sphere.center_, capsule.segment_, &point);

		Vector3 sub = sphere.center_ - point;
		Vector3 Btointer = sub*capsule.radius_ / (sphere.radius_ + capsule.radius_);

		*inter = point + Btointer;
	}

	return true;
}

//--------------------------------------------------------------------------------------------
// 説　明 : 点と線分の距離の二乗を取得
// 引　数 : _point	点
//			_segment	線分
// 戻り値 : 点と線分の距離の二乗
// メ　モ : 平方根を算出しない版
//	線分の端点をA,B	点をCとして、
//	①ABベクトルとACベクトルの内積が負の時、点Aが点Cの最近傍である
//	②BAベクトルとBCベクトルの内積が負の時、点Bが点Cの最近傍である
//	③　①、②に該当しない場合、点Cの射影がACの内側に存在するため、その点が最近傍である
//--------------------------------------------------------------------------------------------
float Collision::GetSqDistancePoint2Segment(const Vector3& _point, const Segment& _segment)
{
	const float epsilon = 1.0e-5f;	// 誤差吸収用の微小な値
	Vector3 SegmentSub;
	Vector3 SegmentPoint;
	Vector3 CP;

	// 線分の始点から終点へのベクトル
	SegmentSub = _segment.end_ - _segment.start_;

	// 線分の始点から点へのベクトル
	SegmentPoint = _point - _segment.start_;
	if (SegmentSub.Dot(SegmentPoint) < epsilon)
	{// ２ベクトルの内積が負なら、線分の始点が最近傍
		return SegmentPoint.Dot(SegmentPoint);
	}

	// 点から線分の終点へのベクトル
	SegmentPoint = _segment.end_ - _point;
	if (SegmentSub.Dot(SegmentPoint) < epsilon)
	{// ２ベクトルの内積が負なら、線分の終点が最近傍
		return SegmentPoint.Dot(SegmentPoint);
	}

	// 上記のどちらにも該当しない場合、線分上に落とした射影が最近傍
	// (本来ならサインで求めるが、外積の大きさ/線分のベクトルの大きさで求まる)
	CP = SegmentSub.Cross(SegmentPoint);

	return CP.Dot(CP) / SegmentSub.Dot(SegmentSub);
}

//--------------------------------------------------------------------------------------------
// 説　明 : 線分と線分の距離の二乗を取得
// 引　数 : _segment0	線分0
//			_segment1	線分1
// 戻り値 : 線分と線分の距離の二乗
// メ　モ : 平方根を算出しない版
//	①直線上の最接近点が両方の線分の内側に存在する時
//	②直線上の最接近点が一方のみの線分の内側に存在する時
//	③直線上の最接近点が両方の線分の外側に存在する時
//	それぞれのケースで二つの線分上の最接近点を求め、その距離を算出する
//--------------------------------------------------------------------------------------------
float Collision::GetSqDistanceSegment2Segment(const Segment& _segment0, const Segment& _segment1)
{
	const float epsilon = 1.0e-5f;	// 誤差吸収用の微小な値
	Vector3 d0, d1, r;
	Vector3 c0, c1;	// 二つの線分上の最接近点
	Vector3 v;		// c1→c0ベクトル
	float a, b, c, e, f;
	float s, t;
	float denom;
	float tnom;

	d0 = _segment0.end_ - _segment0.start_;	// 線分0の方向ベクトル
	d1 = _segment1.end_ - _segment1.start_; // 線分1の方向ベクトル
	r = _segment0.start_ - _segment1.start_; // 線分1の始点から線分0の始点へのベクトル
	a = d0.Dot(d0);		// 線分0の距離の二乗
	e = d1.Dot(d1);		// 線分1の距離の二乗
						//	b = d0.Dot(d1);		// 最適化の為後方に移動した
						//	c = d0.Dot(r);		// 最適化の為後方に移動した
						//	f = d1.Dot(r);		// 最適化の為後方に移動した

						// いづれかの線分の長さが0かどうかチェック
	if (a <= epsilon && e <= epsilon)
	{// 両方長さ0
		v = _segment0.start_ - _segment1.start_;

		return v.Dot(v);
	}

	if (a <= epsilon)
	{// 線分0が長さ0
		return GetSqDistancePoint2Segment(_segment0.start_, _segment1);
	}

	if (e <= epsilon)
	{// 線分1が長さ0
		return GetSqDistancePoint2Segment(_segment1.start_, _segment0);
	}

	b = d0.Dot(d1);
	f = d1.Dot(r);
	c = d0.Dot(r);

	denom = a * e - b * b;	// 常に非負
							// 線分が平行でない場合、直線0上の直線1に対する最近接点を計算、そして
							// 線分0上にクランプ。そうでない場合は任意のsを選択
	if (denom != 0)
	{
		s = Clamp((b * f - c * e) / denom, 0, 1);
	}
	else
	{
		s = 0;
	}

	// 直線1上の最接近点を計算
	tnom = b * s + f;

	if (tnom < 0)
	{
		t = 0;
		s = Clamp(-c / a, 0, 1);
	}
	else if (tnom > e)
	{
		t = 1;
		s = Clamp((b - c) / a, 0, 1);
	}
	else
	{
		t = tnom / e;
	}

	c0 = s * d0 + _segment0.start_;
	c1 = t * d1 + _segment1.start_;
	v = c0 - c1;

	return v.Dot(v);
}


//--------------------------------------------------------------------------------------------
// 説　明 : ３点から三角形を計算（反時計回りに指定）
// 引　数 : _p0	点０
//			_p1	点１
//			_p2 点２
//			_triangle 三角形(結果出力用）
// 戻り値 : なし
// メ　モ : 反時計回り順に３点指定する
//--------------------------------------------------------------------------------------------
void Collision::ComputeTriangle(const Vector3& _p0, const Vector3& _p1, const Vector3& _p2, Triangle* _triangle)
{
	_triangle->P0 = _p0;
	_triangle->P1 = _p1;
	_triangle->P2 = _p2;

	Vector3 P0_P1 = _triangle->P1 - _triangle->P0;
	Vector3 P1_P2 = _triangle->P2 - _triangle->P1;

	_triangle->Normal = P0_P1.Cross(P1_P2);
	_triangle->Normal.Normalize();
}

//--------------------------------------------------------------------------------------------
// 説　明 : 点と三角形の最近接点を計算
// 引　数 : _point	点
//			_segment	線分
//			_closest	最近接点(結果出力用）
// 戻り値 : なし
// メ　モ : 
//--------------------------------------------------------------------------------------------
void Collision::ClosestPtPoint2Triangle(const Vector3& _point, const Triangle& _triangle, Vector3* _closest)
{
	// _pointがP0の外側の頂点領域の中にあるかどうかチェック
	Vector3 P0_P1 = _triangle.P1 - _triangle.P0;
	Vector3 P0_P2 = _triangle.P2 - _triangle.P0;
	Vector3 P0_PT = _point - _triangle.P0;

	float d1 = P0_P1.Dot(P0_PT);
	float d2 = P0_P2.Dot(P0_PT);

	if (d1 <= 0.0f && d2 <= 0.0f)
	{
		// P0が最近傍
		*_closest = _triangle.P0;
		return;
	}

	// _pointがP1の外側の頂点領域の中にあるかどうかチェック
	Vector3 P1_PT = _point - _triangle.P1;

	float d3 = P0_P1.Dot(P1_PT);
	float d4 = P0_P2.Dot(P1_PT);

	if (d3 >= 0.0f && d4 <= d3)
	{
		// P1が最近傍
		*_closest = _triangle.P1;
		return;
	}

	// _pointがP0_P1の辺領域の中にあるかどうかチェックし、あれば_pointのP0_P1上に対する射影を返す
	float vc = d1 * d4 - d3 * d2;
	if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f)
	{
		float v = d1 / (d1 - d3);
		*_closest = _triangle.P0 + v * P0_P1;
		return;
	}

	// _pointがP2の外側の頂点領域の中にあるかどうかチェック
	Vector3 P2_PT = _point - _triangle.P2;

	float d5 = P0_P1.Dot(P2_PT);
	float d6 = P0_P2.Dot(P2_PT);
	if (d6 >= 0.0f && d5 <= d6)
	{
		*_closest = _triangle.P2;
		return;
	}

	// _pointがP0_P2の辺領域の中にあるかどうかチェックし、あれば_pointのP0_P2上に対する射影を返す
	float vb = d5 * d2 - d1 * d6;
	if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f)
	{
		float w = d2 / (d2 - d6);
		*_closest = _triangle.P0 + w * P0_P2;
		return;
	}

	// _pointがP1_P2の辺領域の中にあるかどうかチェックし、あれば_pointのP1_P2上に対する射影を返す
	float va = d3 * d6 - d5 * d4;
	if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f)
	{
		float w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
		*_closest = _triangle.P1 + w * (_triangle.P2 - _triangle.P1);
		return;
	}

	float denom = 1.0f / (va + vb + vc);
	float v = vb * denom;
	float w = vc * denom;
	*_closest = _triangle.P0 + P0_P1 * v + P0_P2 * w;
}

// 点と三角形の当たり判定
bool Collision::CheckPoint2Triangle(const Vector3& _point, const Triangle& _triangle)
{
	//点と三角形は同一平面上にあるものとしています。同一平面上に無い場合は正しい結果になりません
	//線上は外とみなします。
	//ABCが三角形かどうかのチェックは省略...

	// 点0→1、 1→2、 2→0 のベクトルをそれぞれ計算
	Vector3 v01 = _triangle.P1 - _triangle.P0;
	Vector3 v12 = _triangle.P2 - _triangle.P1;
	Vector3 v20 = _triangle.P0 - _triangle.P2;
	// 三角形の各頂点から点へのベクトルをそれぞれ計算
	Vector3 v0p = _point - _triangle.P0;
	Vector3 v1p = _point - _triangle.P1;
	Vector3 v2p = _point - _triangle.P2;
	// 各辺ベクトルと、点へのベクトルの外積を計算
	Vector3 c0 = v01.Cross(v0p);
	Vector3 c1 = v12.Cross(v1p);
	Vector3 c2 = v20.Cross(v2p);
	// 内積で同じ方向かどうか調べる
	float dot01 = c0.Dot(c1);
	float dot02 = c0.Dot(c2);
	// 外積ベクトルが全て同じ方向なら、三角形の内側に点がある
	if (dot01 > 0 && dot02 > 0)
	{
		return true;
	}

	//三角形の外側に点がある
	return false;

}

//--------------------------------------------------------------------------------------------
// 説　明 : 球と法線付き三角形の当たりチェック
// 引　数 : _sphere		球
//			_tri		法線付き三角形
//			_inter		交点（省略可）
// 戻り値 : 交差しているか否か
// メ　モ : 裏面の当たりはとらない
//--------------------------------------------------------------------------------------------
bool Collision::CheckSphere2Triangle(const Sphere& _sphere, const Triangle& _triangle, Vector3 *_inter)
{
	Vector3 p;

	// 球の中心に対する最近接点である三角形上にある点pを見つける
	ClosestPtPoint2Triangle(_sphere.center_, _triangle, &p);

	Vector3 v = p - _sphere.center_;

	// 球と三角形が交差するのは、球の中心から点pまでの距離が球の半径よりも小さい場合
	if (v.Dot(v) <= _sphere.radius_ * _sphere.radius_)
	{
		if (_inter)
		{
			*_inter = p;
		}

		return true;
	}

	return false;

	// 球と平面（三角形が乗っている平面）の当たり判定
	// 球と平面の距離を計算
	float ds = _sphere.center_.Dot(_triangle.Normal);
	float dt = _triangle.P0.Dot(_triangle.Normal);
	float dist = ds - dt;
	// 距離が半径以上なら、当たらない
	if (fabsf(dist) > _sphere.radius_)	return false;
	// 中心点を平面に射影したとき、三角形の内側にあれば、当たっている
	// 射影した座標
	Vector3 center = -dist * _triangle.Normal + _sphere.center_;

	// 三角形の外側になければ、当たっていない
	if (!CheckPoint2Triangle(center, _triangle))	return false;

	if (_inter)
	{
		*_inter = center;	// 交点をコピー
	}

	return true;
}

//--------------------------------------------------------------------------------------------
// 説　明 : 線分（有向）と法線付き三角形の当たりチェック
// 引　数 : _segment		光線の線分（start→endが正方向）
//			_tri		法線付き三角形
//			_inter		交点（省略可）
// 戻り値 : 交差しているか否か
// メ　モ : 裏面の当たりはとらない
//--------------------------------------------------------------------------------------------
bool Collision::CheckSegment2Triangle(const Segment& _segment, const Triangle& _triangle, Vector3 *_inter)
{
	const float epsilon = -1.0e-5f;	// 誤差吸収用の微小な値
	Vector3 LayV;		// 線分の終点→始点
	Vector3 tls;		// 三角形の頂点0→線分の始点
	Vector3 tle;		// 三角形の頂点0→線分の終点
	float 	distl0;
	float 	distl1;
	float 	dp;
	float 	denom;
	float 	t;
	Vector3	s;		// 直線と平面との交点
	Vector3 st0;		// 交点→三角形の頂点0
	Vector3 st1;		// 交点→三角形の頂点1
	Vector3 st2;		// 交点→三角形の頂点2
	Vector3 t01;		// 三角形の頂点0→頂点1
	Vector3 t12;		// 三角形の頂点1→頂点2
	Vector3 t20;		// 三角形の頂点2→頂点0
	Vector3	m;

	// 線分の始点が三角系の裏側にあれば、当たらない
	tls = _segment.start_ - _triangle.P0;
	distl0 = tls.Dot(_triangle.Normal);	// 線分の始点と平面の距離
	if (distl0 <= epsilon) return false;

	// 線分の終点が三角系の表側にあれば、当たらない
	tle = _segment.end_ - _triangle.P0;
	distl1 = tle.Dot(_triangle.Normal);	// 線分の終点と平面の距離
	if (distl1 >= -epsilon) return false;

	// 直線と平面との交点sを取る
	denom = distl0 - distl1;
	t = distl0 / denom;
	LayV = _segment.end_ - _segment.start_;	// 線分の方向ベクトルを取得
	s = t * LayV + _segment.start_;

	// 交点が三角形の内側にあるかどうかを調べる。
	// 三角形の内側にある場合、交点から各頂点へのベクトルと各辺ベクトルの外積（三組）が、
	// 全て法線と同じ方向を向く
	// 一つでも方向が一致しなければ、当たらない。
	st0 = _triangle.P0 - s;
	t01 = _triangle.P1 - _triangle.P0;
	m = st0.Cross(t01);
	dp = m.Dot(_triangle.Normal);
	if (dp <= epsilon) return false;

	st1 = _triangle.P1 - s;
	t12 = _triangle.P2 - _triangle.P1;
	m = st1.Cross(t12);
	dp = m.Dot(_triangle.Normal);
	if (dp <= epsilon) return false;

	st2 = _triangle.P2 - s;
	t20 = _triangle.P0 - _triangle.P2;
	m = st2.Cross(t20);
	dp = m.Dot(_triangle.Normal);
	if (dp <= epsilon) return false;

	if (_inter)
	{
		*_inter = s;	// 交点をコピー
	}

	return true;
}