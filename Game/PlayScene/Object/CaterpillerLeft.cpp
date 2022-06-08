/**
* @file CaterpillerLeft.cpp
* @brief �L���^�s�^�̃N���X
* @author ���V�x��
* @date 2022/05/01
* @details �{�X02�̃^�C�����̃N���X
*/
#include "pch.h"

#include "CaterpillerLeft.h"
#include "../BossFactory.h"

//--------------------------------------------------------
// �T�v�F�{�X�p�[�c��ǉ�����
// ���� (bossParts)�FHeartObject�̃��j�[�N�|�C���^ 
// �߂�l�F�Ȃ�
//--------------------------------------------------------
void CaterpillerLeft::AddBossParts(std::unique_ptr<HeartObject> bossParts)
{
	// �^���N�p�[�c��ǉ�����
	mpBossParts.push_back(std::move(bossParts));
}

//----------------------------------------------------------
// �T�v�F�R���X�g���N�^
// ����(offset)�F�f�̂Ƃ̋���
// ����(pBulletManager)�F�e�̔��ˊǗ����
// �߂�l�F�Ȃ�
//----------------------------------------------------------
CaterpillerLeft::CaterpillerLeft(
	const DirectX::SimpleMath::Vector3& offset,
	BulletManager* pBulletManager
) :
	mpBossParts{},
	mPosOffset(offset),
	mAngleOffset(DirectX::SimpleMath::Vector3::Zero),
	mpBullets(pBulletManager)
{
	SetObjectPos(DirectX::SimpleMath::Vector3::Zero);
	SetObjectDirection(DirectX::SimpleMath::Vector3::Zero);
	SetObjectSpeed(DirectX::SimpleMath::Vector3::Zero);
	SetActive(true);
	SetHP(10);
}

//--------------------------------------------
// �T�v�F�f�X�g���N�^
//--------------------------------------------
CaterpillerLeft::~CaterpillerLeft()
{
	// �I���������Ă�
	Finalize();
}

//-------------------------------------------------------
// �T�v�F������
// ���� (bossFactory):�{�X�̐����N���X
// �߂�l�F�Ȃ�
//-------------------------------------------------------
void CaterpillerLeft::Initialize(BossFactory* bossFactory)
{
	UNREFERENCED_PARAMETER(bossFactory);
}

//------------------------------------------------------
// �T�v�F�X�V
// ���� (position)�F���W
// ���� (angle)�F�p�x
// ���� (offset)�F�f�̂Ƃ̋���
// ���� (playerPos)�F�v���C���[�̍��W
// ���� (stateNum)�F�{�X�̏��
// �߂�l�F�Ȃ�
//------------------------------------------------------
void CaterpillerLeft::Update(
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Vector3& angle,
	const DirectX::SimpleMath::Vector3& offset,
	const DirectX::SimpleMath::Vector3& playerPos,
	const int& stateNum
)
{
	// �ʒu��ݒ肷��
	SetObjectPos(position);

	// ������ݒ肷��
	SetObjectDirection(angle);

	// �����̃I�t�Z�b�g���w�肷��
	mAngleOffset = offset;
	if (GetHP() <= 0)
	{
		SetActive(false);
	}

	// �ċA�I�Ƀ^���N�p�[�c��Update�֐����Ăяo��
	for (auto& bossParts : mpBossParts)
	{
		// Update�֐����Ăяo��
		bossParts->Update(position, angle, offset, playerPos, stateNum);
	}
}

//---------------------------------------------------------------
// �T�v�F�`��
// ����(commonStates)�F�R�����X�e�C�g�̃|�C���^
// ����(camera)�F�J�����̃|�C���^
// �߂�l�F�Ȃ�
//---------------------------------------------------------------
void CaterpillerLeft::Draw(DirectX::CommonStates* commonStates, Camera* camera)
{
	mCamera = camera;
	auto pRM = ResourceManager::GetInstance();
	//�f�o�C�X�R���e�L�X�g�̎擾
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	auto context = pDR->GetD3DDeviceContext();

	// �ˉe�s��̎擾
	DirectX::SimpleMath::Matrix projection = camera->GetProjectionMatrix();
	// �r���[�s��̎擾
	DirectX::SimpleMath::Matrix view = camera->GetViewMatrix();

	// ���[���h���W�̎擾
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::CreateTranslation(GetObjectPos());

	// ���f���̉�]
	DirectX::SimpleMath::Quaternion q = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
		GetObjectDirection().y * 0.05f,
		GetObjectDirection().x * 0.05f,
		GetObjectDirection().z * 0.05f
	);

	pRM->GetCmoModel("CaterpillerLeft")->Draw(
		context,
		*commonStates,
		DirectX::SimpleMath::Matrix::CreateFromQuaternion(q) * world,
		view,
		projection
	);

	// �ċA�I�Ƀ^���N�p�[�c��Update�֐����Ăяo��
	for (auto& bossParts : mpBossParts)
	{
		// Update�֐����Ăяo��
		bossParts->Draw(commonStates, camera);
	}
}

//----------------------------------------------
// �T�v�F�I������
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//----------------------------------------------
void CaterpillerLeft::Finalize()
{
}

//----------------------------------------------
// �T�v�F����
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//----------------------------------------------
void CaterpillerLeft::Move()
{
}

//-----------------------------------------------
// �T�v�F�����蔻��
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//-----------------------------------------------
void CaterpillerLeft::Collision()
{
	// �p�[�c����ł������Ă���Ȃ珈�����Ȃ�
	bool enp = true;
	for (unsigned int i = 0; i < mpBossParts.size(); i++)
	{
		if (mpBossParts[i]->GetActive())
		{
			enp = false;
		}
	}

	if (enp)
	{
		// ���ׂĂ̒e�Ɠn���ꂽ�ΏۂƂ̔�������
		for (unsigned int i = 0; i < 512; i++)
		{
			// ����̏����Ȃ�Δ��肵�Ȃ�
			if (
				!mpBullets->GetBullet(i)->GetActive() ||			// �e�����ˏ�ԂłȂ�
				mpBullets->GetBullet(i)->GetShooterType() == static_cast<int>(Bullet::eShooterType::ENEMY_SHOT)
				)
			{
				continue;
			}


			// �����蔻��p�̈ꎞ�ϐ�
			Collision::Sphere bullet;
			Collision::Sphere enemy;

			bullet.center = mpBullets->GetBullet(i)->GetObjectPos();
			bullet.radius = 1.0f;

			enemy.center = GetObjectPos();
			enemy.center.y += 5.0f;
			enemy.radius = 5.0f;

			// �������Ă��Ȃ���Ύ���
			if (!Collision::HitCheckSphereToSphere(bullet, enemy))
			{
				continue;
			}

			// �_���[�W�����G�l�~�[
			mpBullets->GetBullet(i)->SetActive(false);

			DirectX::SimpleMath::Vector3 a = mpBullets->GetBullet(i)->GetObjectPos();
			a.z -= -5.0f;

			int hp = GetHP();
			hp -= 1;
			SetHP(hp);
		}
		return;
	}

	// �ċA�I�Ƀ^���N�p�[�c��Update�֐����Ăяo��
	for (auto& bossParts : mpBossParts)
	{
		// Update�֐����Ăяo��
		bossParts->Collision();
	}
}

//-------------------------------------------------------
// �T�v�F�p�[�c������
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//--------------------------------------------------------
void CaterpillerLeft::DeleteParts()
{
	//mpBossParts.pop_back();
}

// �Q�b�^�[�A�Z�b�^�[------------------------------------------------------------------------------------------

//---------------------------------------
// �T�v�F���W�̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(Vector3)�F�I�u�W�F�N�g�̍��W
//---------------------------------------
DirectX::SimpleMath::Vector3 CaterpillerLeft::GetObjectPos() const
{
	return HeartObject::GetObjectPos();
}

//---------------------------------------
// �T�v�F���W�̃Z�b�^�[
// ����(pos)�F�I�u�W�F�N�g�̍��W
// �߂�l�F�Ȃ�
//---------------------------------------
void CaterpillerLeft::SetObjectPos(const DirectX::SimpleMath::Vector3& pos)
{
	HeartObject::SetObjectPos(pos);
}

//---------------------------------------
// �T�v�F�����̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(Vector3)�F�I�u�W�F�N�g�̍��W
//---------------------------------------
DirectX::SimpleMath::Vector3 CaterpillerLeft::GetObjectDirection() const
{
	return HeartObject::GetObjectDirection();
}

//---------------------------------------
// �T�v�F�����̃Z�b�^�[
// ����(direction)�F�I�u�W�F�N�g�̌���
// �߂�l�F�Ȃ�
//---------------------------------------
void CaterpillerLeft::SetObjectDirection(const DirectX::SimpleMath::Vector3& direction)
{
	HeartObject::SetObjectDirection(direction);
}

//---------------------------------------
// �T�v�F�����̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(Vector3)�F�I�u�W�F�N�g�̑���
//---------------------------------------
DirectX::SimpleMath::Vector3 CaterpillerLeft::GetObjectSpeed() const
{
	return HeartObject::GetObjectSpeed();
}

//---------------------------------------
// �T�v�F�����̃Z�b�^�[
// ����(speed)�F�I�u�W�F�N�g�̑���
// �߂�l�F�Ȃ�
//---------------------------------------
void CaterpillerLeft::SetObjectSpeed(const DirectX::SimpleMath::Vector3& speed)
{
	HeartObject::SetObjectSpeed(speed);
}

//---------------------------------------
// �T�v�F�g�p��Ԃ̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(bool)�F�I�u�W�F�N�g�̎g�p���
//---------------------------------------
bool CaterpillerLeft::GetActive() const
{
	return HeartObject::GetActive();
}

//---------------------------------------
// �T�v�F�g�p��Ԃ̃Z�b�^�[
// ����(active)�F�I�u�W�F�N�g�̎g�p���
// �߂�l�F�Ȃ�
//---------------------------------------
void CaterpillerLeft::SetActive(const bool& active)
{
	HeartObject::SetActive(active);
}

//---------------------------------------
// �T�v�FHP�̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(Vector3)�F�I�u�W�F�N�g��HP
//---------------------------------------
int CaterpillerLeft::GetHP() const
{
	return HeartObject::GetHP();
}

//---------------------------------------
// �T�v�FHP�̃Z�b�^�[
// ����(hp)�F�I�u�W�F�N�g��HP
// �߂�l�F�Ȃ�
//---------------------------------------
void CaterpillerLeft::SetHP(const int& hp)
{
	HeartObject::SetHP(hp);
}
