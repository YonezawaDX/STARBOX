/**
* @file Enemy.cpp
* @brief �G�̃N���X
* @author ���V�x��
* @date 2021/12/04
* @details �G
*/
#include "pch.h"
#include "Enemy.h"

//----------------------------------------------------------
// �T�v�F�R���X�g���N�^
//----------------------------------------------------------
Enemy::Enemy()
	: mpBulletManager{}
	, mEnemyType(0)
	, mShotTimer(0)
{
}

//--------------------------------------------
// �T�v�F�f�X�g���N�^
//--------------------------------------------
Enemy::~Enemy()
{
}

//-------------------------------------------------------
// �T�v�F������
// ���� : �Ȃ�
// �߂�l�F�Ȃ�
//-------------------------------------------------------
void Enemy::Initialize()
{
}

//-------------------------------------------------------
// �T�v�F������
// ���� (modelType)�F�G�̃��f���̃^�C�v
// ���� (enemyType)�F�G�̎��
// ���� (pos)�F���W
// ���� (angle)�F�p�x
// ���� (hp)�F�̗�
// ���� (pBulletManager)�F�e���˗p
// �߂�l�F�Ȃ�
//-------------------------------------------------------
void Enemy::Initialize(
	Model3D* modelType,
	int enemyType,
	DirectX::SimpleMath::Vector3 pos,
	DirectX::SimpleMath::Vector3 angle ,
	int hp,
	BulletManager* pBulletManager
)
{
	UNREFERENCED_PARAMETER(modelType);
	// �e�̊Ǘ��҂�ۑ�
	mpBulletManager = pBulletManager;
	
	// �G�̎�ނ�ۑ�
	mEnemyType = enemyType;

	// ���W�̕ۑ�
	SetObjectPos(pos);

	// �G���g�p��ԂƂ���
	SetActive(true);

	// �G�̌���
	SetObjectDirection(angle);

	// HP�̃Z�b�g
	this->SetHP(hp);
}

//------------------------------------------------------
// �T�v�F�X�V
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//------------------------------------------------------
void Enemy::Update()
{
	// �A�N�e�B�u��ԂłȂ���Ώ��������Ȃ�
	if (!this->GetActive())
	{
		return;
	}


	DirectX::SimpleMath::Vector3 enemyPos = GetObjectPos();

	switch (mEnemyType)
	{
		case static_cast<int>(eEnemyType::NORMAL):
		{

			enemyPos.z += 0.1f;

			// ���ˊԊu�p�^�C�}�[��i�߂�
			++mShotTimer %= 60;

			// ���Ԃ�������e����
			if (mShotTimer == 0)
			{
				//mpBulletManager->Shot(1,enemyPos, DirectX::SimpleMath::Vector3::Zero);
			}
			break;
		}
		case static_cast<int>(eEnemyType::ROTATE):
		{
			break;
		}
		case static_cast<int>(eEnemyType::TRACK):
		{
			//enemyPos.z += 0.2f;
			DirectX::SimpleMath::Vector3 vel = GetObjectDirection();
			vel.Normalize();

			enemyPos -= vel * 0.25f;
			
			// ���ˊԊu�p�^�C�}�[��i�߂�
			++mShotTimer %= 60;

			// ���Ԃ�������e����
			if (mShotTimer == 0)
			{
				//mpBulletManager->Shot(1,enemyPos, DirectX::SimpleMath::Vector3::Zero);
			}
			break;
		}
		default:
			break;
	}

	// ���W�����肷��
	SetObjectPos(enemyPos);

	// ��ʊO�ɏo���疢�g�p��Ԃɂ���
	if (
		GetObjectPos().z > 50.0f ||
		GetObjectPos().z < -1000.0f
		)
	{
		SetActive(false);
	}

}

//---------------------------------------------------------------
// �T�v�F�`��
// ����(commonStates)�F�R�����X�e�C�g�̃|�C���^
// ����(camera)�F�J�����̃|�C���^
// �߂�l�F�Ȃ�
//---------------------------------------------------------------
void Enemy::Draw(DirectX::CommonStates* commonStates, Camera* camera)
{
	// �A�N�e�B�u��ԂłȂ���Ώ������Ȃ�
	if (!this->GetActive())
	{
		return;
	}
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


	pRM->GetCmoModel("Enemy")->Draw(
		context,
		*commonStates,
		world,
		view,
		projection
	);

}

//----------------------------------------------
// �T�v�F�I������
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//----------------------------------------------
void Enemy::Finalize()
{
}

//----------------------------------------------
// �T�v�F����
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//----------------------------------------------
void Enemy::Move()
{
}
//----------------------------------------------
// �T�v�F�_���[�W
// ����(damage)�F�_���[�W�̒l
// �߂�l�F�Ȃ�
//----------------------------------------------
void Enemy::Damage(int damage)
{
	damage;
	SetActive(false);
}

// �Q�b�^�[�A�Z�b�^�[----------------------------------------------------------------

//---------------------------------------
// �T�v�F���W�̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(Vector3)�F�I�u�W�F�N�g�̍��W
//---------------------------------------
DirectX::SimpleMath::Vector3 Enemy::GetObjectPos() const
{
	return HeartObject::GetObjectPos();
}
//---------------------------------------
// �T�v�F���W�̃Z�b�^�[
// ����(pos)�F�I�u�W�F�N�g�̍��W
// �߂�l�F�Ȃ�
//---------------------------------------
void Enemy::SetObjectPos(const DirectX::SimpleMath::Vector3& pos)
{
	HeartObject::SetObjectPos(pos);
}

//---------------------------------------
// �T�v�F�����̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(Vector3)�F�I�u�W�F�N�g�̍��W
//---------------------------------------
DirectX::SimpleMath::Vector3 Enemy::GetObjectDirection() const
{
	return HeartObject::GetObjectDirection();
}
//---------------------------------------
// �T�v�F�����̃Z�b�^�[
// ����(direction)�F�I�u�W�F�N�g�̌���
// �߂�l�F�Ȃ�
//---------------------------------------
void Enemy::SetObjectDirection(const DirectX::SimpleMath::Vector3& direction)
{
	HeartObject::SetObjectDirection(direction);
}

//---------------------------------------
// �T�v�F�����̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(Vector3)�F�I�u�W�F�N�g�̑���
//---------------------------------------
DirectX::SimpleMath::Vector3 Enemy::GetObjectSpeed() const
{
	return HeartObject::GetObjectSpeed();
}
//---------------------------------------
// �T�v�F�����̃Z�b�^�[
// ����(speed)�F�I�u�W�F�N�g�̑���
// �߂�l�F�Ȃ�
//---------------------------------------
void Enemy::SetObjectSpeed(const DirectX::SimpleMath::Vector3& speed)
{
	HeartObject::SetObjectSpeed(speed);
}

//---------------------------------------
// �T�v�F�g�p��Ԃ̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(bool)�F�I�u�W�F�N�g�̎g�p���
//---------------------------------------
bool Enemy::GetActive() const
{
	return HeartObject::GetActive();
}

//---------------------------------------
// �T�v�F�g�p��Ԃ̃Z�b�^�[
// ����(active)�F�I�u�W�F�N�g�̎g�p���
// �߂�l�F�Ȃ�
//---------------------------------------
void Enemy::SetActive(const bool& act)
{
	HeartObject::SetActive(act);
}

//---------------------------------------
// �T�v�FHP�̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(Vector3)�F�I�u�W�F�N�g��HP
//---------------------------------------
int Enemy::GetHP() const
{
	return HeartObject::GetHP();
}
//---------------------------------------
// �T�v�FHP�̃Z�b�^�[
// ����(hp)�F�I�u�W�F�N�g��HP
// �߂�l�F�Ȃ�
//---------------------------------------
void Enemy::SetHP(const int& hp)
{
	HeartObject::SetHP(hp);
}
