/**
* @file Bullet.cpp
* @brief �e�N���X
* @author ���V�x��
* @date 2021/12/01
* @details �e
*/
#include "pch.h"
#include "Bullet.h"

//-------------------------------------------------------------------
// �T�v�F�R���X�g���N�^
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//-------------------------------------------------------------------
Bullet::Bullet()
	: mpBulletModel3D{}
	, mShooterType(eShooterType::PLAYER_SHOT)
	, mBulletAnglePos(DirectX::SimpleMath::Vector3::Zero)
	, mIsActive(true)
{
}

//---------------------------------------------------------
// �T�v�F�f�X�g���N�^
//---------------------------------------------------------
Bullet::~Bullet()
{
}

//----------------------------------------------------------
// �T�v�F������
// ����()�F�Ȃ�
// �߂�l�F�Ȃ�
//----------------------------------------------------------
void Bullet::Initialize()
{
}

//----------------------------------------------------------
// �T�v�F������
// ����(bulletType)�F�e�̃^�C�v
// ����(shooterType)�F�e���g���҂̎��
// ����(pos)�F���W
// ����(angle)�F�p�x
// �߂�l�F�Ȃ�
//----------------------------------------------------------
void Bullet::Initialize(
	Model3D* bulletType,
	int shooterType, 
	DirectX::SimpleMath::Vector3 pos,
	DirectX::SimpleMath::Vector3 angle
)
{
	// ���f���ւ̃|�C���^���i�[����
	mpBulletModel3D = bulletType;

	// ���˂���L�����̕ۑ�
	mShooterType = static_cast<eShooterType>(shooterType);

	// ���ˎ��̍��W�̕ۑ�
	SetObjectPos(pos);

	// ���ˎ��̋@�̂̊p�x���擾�����ˊp���v�Z����
	SetObjectDirection(angle);

	// �g�p���ɂ���
	SetActive(true);
}


//-----------------------------------------------------------
// �T�v�F�X�V
// ����()�F�Ȃ�
// �߂�l�F�Ȃ�
//-----------------------------------------------------------
void Bullet::Update()
{
	// �g�p���łȂ���Ώ������Ȃ�
	if (!GetActive())
	{
		return;
	}
	Move();

	// ��ʊO�ɏo���疢�g�p��Ԃɂ���
	if (
		GetObjectPos().z > 100.0f||
		GetObjectPos().z < -1000.0f
		)
	{
		SetActive(false);
	}

}

//-------------------------------------------------------------
// �T�v�F�`��
// ����(commonStates)�F�R�����X�e�C�g
// ����(camera)�F�J����
// �߂�l�F�Ȃ�
//-------------------------------------------------------------
void Bullet::Draw(DirectX::CommonStates* commonStates, Camera* camera)
{
	// �g�p���łȂ���Ώ������Ȃ�
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


	pRM->GetCmoModel("Bullet")->Draw(
		context,
		*commonStates,
		DirectX::SimpleMath::Matrix::CreateFromQuaternion(q) * world,
		view,
		projection
	);
}

//--------------------------------------------------------------
// �T�v�F�I������
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//--------------------------------------------------------------
void Bullet::Finalize()
{
}


//--------------------------------------------------------------
// �T�v�F����
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//--------------------------------------------------------------
void Bullet::Move()
{
	DirectX::SimpleMath::Vector3 bulletPos = GetObjectPos();
	switch (mShooterType)
	{
		case eShooterType::PLAYER_SHOT:
		{
			bulletPos.x -= atanf((DirectX::XMConvertToRadians(GetObjectDirection().y)) * 4.5f);
			bulletPos.y += atanf((DirectX::XMConvertToRadians(GetObjectDirection().x)) * 4.5f);

			bulletPos.z -= 1.5f;
			SetObjectPos(bulletPos);

			break;
		}
		case eShooterType::ENEMY_SHOT:
		{
			break;
		}
		case eShooterType::BOSS_SHOT:
		{
			DirectX::SimpleMath::Vector3 vel = GetObjectDirection();
			vel.Normalize();

			bulletPos -= vel * 0.25f;

			SetObjectPos(bulletPos);
			break;
		}
		default:
			assert("�e������܂���");
			break;
	}
}


//--------------------------------------------------------------
// �T�v�F�_���[�W
// ����(damage)�F�_���[�W�̒l
// �߂�l�F�Ȃ�
//--------------------------------------------------------------
void Bullet::Damage(int damage)
{
	UNREFERENCED_PARAMETER(damage);
}

// �Q�b�^�Z�b�^---------------------------------------------------------------------------------

//---------------------------------------
// �T�v�F���W�̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(Vector3)�F�I�u�W�F�N�g�̍��W
//---------------------------------------
DirectX::SimpleMath::Vector3 Bullet::GetObjectPos() const
{
	return Object::GetObjectPos();
}
//---------------------------------------
// �T�v�F���W�̃Z�b�^�[
// ����(pos)�F�I�u�W�F�N�g�̍��W
// �߂�l�F�Ȃ�
//---------------------------------------
void Bullet::SetObjectPos(const DirectX::SimpleMath::Vector3& pos)
{
	Object::SetObjectPos(pos);
}

//---------------------------------------
// �T�v�F�g�p��Ԃ̃Q�b�^�[
// ����()�F�Ȃ�
// �߂�l(bool)�F�g�p���
//---------------------------------------
bool Bullet::GetActive() const
{
	return MoveObject::GetActive();
}
//---------------------------------------
// �T�v�F�g�p��Ԃ̃Z�b�^�[
// ����(act)�F�g�p���
// �߂�l�F�Ȃ�
//---------------------------------------
void Bullet::SetActive(const bool& act)
{
	MoveObject::SetActive(act);
}

//---------------------------------------
// �T�v�F���˃^�C�v�̃Q�b�^�[
// ����()�F�Ȃ�
// �߂�l(int)�F���˂���^�C�v
//---------------------------------------
Bullet::eShooterType Bullet::GetShooterType() const
{
	return mShooterType;
}
//---------------------------------------
// �T�v�F���˃^�C�v�̃Z�b�^�[
// ����(type)�F���˂���^�C�v
// �߂�l�F�Ȃ�
//---------------------------------------
void Bullet::SetShooterType(const eShooterType type)
{
	mShooterType = type;
}
