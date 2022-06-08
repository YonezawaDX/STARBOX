/**
* @file Collision.h
* @brief 当たり判定のクラス
* @author 米澤駿介
* @date 2022/04/26
* @details 当たり判定まとめ
*/
#pragma once

#include <SimpleMath.h>

/**
* @brief 当たり判定のクラス
* @details 当たり判定
*/
class Collision
{
public:
	// 境界ボリュームの構造体---------------------------------------------------------------------------
	
	/**
	* @struct 球の構造体
	* @details 球の構造体、中心と半径
	*/
	struct Sphere
	{
		DirectX::SimpleMath::Vector3 center;	//! 球の中心
		float radius;							//! 球の半径
	};

	/**
	* @struct 箱の構造体
	* @details 箱の構造体、中心と半径
	*/
	struct Box
	{
		DirectX::SimpleMath::Vector3 center;	//! BOXの中心点 
		DirectX::SimpleMath::Vector3 radius;	//! 幅の半分
	};

	// 境界ボリューム同士の当たり判定-------------------------------------------------------------------
	
	/**
	* @brief 球と球の当たり判定
	* @param (shpere1) １つ目の球
	* @param (shpere2) ２つ目の球
	* @return bool 衝突した(ture),衝突していない(false)
	*/
	static bool HitCheckSphereToSphere(const Sphere& sphere1, const Sphere& sphere2)
	{
		// 中心間の距離の平方を計算
		DirectX::SimpleMath::Vector3 d = sphere1.center - sphere2.center;
		float dist2 = d.Dot(d);
		// 平方した距離が平方した半径の合計よりも小さい場合に球は交差している
		float radiusSum = sphere1.radius + sphere2.radius;
		return dist2 <= radiusSum * radiusSum;
	}

	/**
	* @brief 球と箱の当たり判定
	* @param (shpere) 球
	* @param (box) 箱
	* @return bool 衝突した(ture),衝突していない(false)
	*/
	static bool HitCheckSphereToBox(const Sphere& sphere, const Box& box)
	{
		float sqDist = SqDistPointBox(sphere.center, box);
		return sqDist <= sphere.radius * sphere.radius;
	}

	// 衝突判定に必要な補助関数群----------------------------------------------------------------------------
		
	/**
	* @brief 点とボックスの間の最短距離の平方を計算する関数
	* @param (p) 座標
	* @param (b) 箱
	* @return float 最短距離を渡す 
	*/
	static float SqDistPointBox(const DirectX::SimpleMath::Vector3& p, const Box& b)
	{
		float point[3] = { p.x, p.y, p.z };
		float min[3] = { b.center.x - b.radius.x, b.center.y - b.radius.y, b.center.z - b.radius.z, };
		float max[3] = { b.center.x + b.radius.x, b.center.y + b.radius.y, b.center.z + b.radius.z, };

		float sqDist = 0.0f;
		for (int i = 0; i < 3; i++)
		{
			float v = point[i];
			if (v < min[i]) sqDist += (min[i] - v) * (min[i] - v);
			if (v > max[i]) sqDist += (v - max[i]) * (v - max[i]);
		}
		return sqDist;
	}
};