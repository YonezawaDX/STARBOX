/**
* @file Collision.h
* @brief �����蔻��̃N���X
* @author ���V�x��
* @date 2022/04/26
* @details �����蔻��܂Ƃ�
*/
#pragma once

#include <SimpleMath.h>

/**
* @brief �����蔻��̃N���X
* @details �����蔻��
*/
class Collision
{
public:
	// ���E�{�����[���̍\����---------------------------------------------------------------------------
	
	/**
	* @struct ���̍\����
	* @details ���̍\���́A���S�Ɣ��a
	*/
	struct Sphere
	{
		DirectX::SimpleMath::Vector3 center;	//! ���̒��S
		float radius;							//! ���̔��a
	};

	/**
	* @struct ���̍\����
	* @details ���̍\���́A���S�Ɣ��a
	*/
	struct Box
	{
		DirectX::SimpleMath::Vector3 center;	//! BOX�̒��S�_ 
		DirectX::SimpleMath::Vector3 radius;	//! ���̔���
	};

	// ���E�{�����[�����m�̓����蔻��-------------------------------------------------------------------
	
	/**
	* @brief ���Ƌ��̓����蔻��
	* @param (shpere1) �P�ڂ̋�
	* @param (shpere2) �Q�ڂ̋�
	* @return bool �Փ˂���(ture),�Փ˂��Ă��Ȃ�(false)
	*/
	static bool HitCheckSphereToSphere(const Sphere& sphere1, const Sphere& sphere2)
	{
		// ���S�Ԃ̋����̕������v�Z
		DirectX::SimpleMath::Vector3 d = sphere1.center - sphere2.center;
		float dist2 = d.Dot(d);
		// �������������������������a�̍��v�����������ꍇ�ɋ��͌������Ă���
		float radiusSum = sphere1.radius + sphere2.radius;
		return dist2 <= radiusSum * radiusSum;
	}

	/**
	* @brief ���Ɣ��̓����蔻��
	* @param (shpere) ��
	* @param (box) ��
	* @return bool �Փ˂���(ture),�Փ˂��Ă��Ȃ�(false)
	*/
	static bool HitCheckSphereToBox(const Sphere& sphere, const Box& box)
	{
		float sqDist = SqDistPointBox(sphere.center, box);
		return sqDist <= sphere.radius * sphere.radius;
	}

	// �Փ˔���ɕK�v�ȕ⏕�֐��Q----------------------------------------------------------------------------
		
	/**
	* @brief �_�ƃ{�b�N�X�̊Ԃ̍ŒZ�����̕������v�Z����֐�
	* @param (p) ���W
	* @param (b) ��
	* @return float �ŒZ������n�� 
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