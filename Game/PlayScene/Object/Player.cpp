/**
* @file Player.cpp
* @brief �v���C���[�̃N���X
* @author ���V�x��
* @date 2022/04/26
* @details �v���C���[�A�ړ�������e��������
*/
#include "pch.h"
#include "Player.h"
#include <Keyboard.h>
#include "Libraries/MyLibraries/ResourceManager.h"
#include "DeviceResources.h"
#include "Libraries/MyLibraries/InputManager.h"

// �萔-------------------------------------------------
// �������W
const DirectX::SimpleMath::Vector3 Player::START_POS = DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f);
// �̗�
const int Player::HP = 100;
// �����x
const float Player::ACCELERATION = 0.005f;
// ����
const float Player::ANGLE = 0.5f;
// �v���C���[���~�߂鑬�x
const float Player::STOP_PLAYER = 0.01f;

// �����̌��E�l
const DirectX::SimpleMath::Vector3 Player::LIMIT_SPEED_MIN = DirectX::SimpleMath::Vector3(-5.0f, -5.0f, -5.0f);
const DirectX::SimpleMath::Vector3 Player::LIMIT_SPEED_MAX = DirectX::SimpleMath::Vector3(5.0f, 5.0f, 5.0f);

// �ʒu�̌��E�l
const DirectX::SimpleMath::Vector3 Player::LIMIT_POS_MIN = DirectX::SimpleMath::Vector3(-20.0f, 1.0f, 0.0f);
const DirectX::SimpleMath::Vector3 Player::LIMIT_POS_MAX = DirectX::SimpleMath::Vector3(20.0f, 10.0f, 0.0f);

// �V���b�g�̃C���^�[�o��
const int Player::SHOT_INTERVAL = 20;

//------------------------------------------------------

//------------------------------------------------------------------
// �T�v�F�R���X�g���N�^
// ����(pBulletManager)�F�e�̊Ǘ���
//------------------------------------------------------------------
Player::Player(BulletManager* pBulletManager)
	: mPlayerSpeed(DirectX::SimpleMath::Vector3::Zero)
	, mPlayerAngle(DirectX::SimpleMath::Vector3::Zero)
	, mPlayerMoveFlag(false)
	, mpBulletManager(pBulletManager)
	, mShootIntervalTimer(0)
	, mPlayerPos(DirectX::SimpleMath::Vector3::Zero)
{
}

//------------------------------------------------------------------
// �T�v�F�f�X�g���N�^
// �����F�Ȃ�
//-------------------------------------------------------------------
Player::~Player()
{
}

//----------------------------------------------------
// �T�v�F������
// ���� : �Ȃ�
// �߂�l�F�Ȃ�
//----------------------------------------------------
void Player::Initialize()
{
	// �e��p�����[�^������������
	SetObjectPos(START_POS);
	SetObjectDirection(DirectX::SimpleMath::Vector3::Zero);
	SetObjectSpeed(DirectX::SimpleMath::Vector3::Zero);
	SetActive(true);
	SetHP(HP);
}

//----------------------------------------------------
// �T�v�F�X�V
// ����:�Ȃ�
// �߂�l�F�Ȃ�
//----------------------------------------------------
void Player::Update()
{
	// �v���C���𓮂���
	Move();

	// �e�𔭎˂���
	Shot();
}

//----------------------------------------------------------------------
// �T�v�F�`��
// ����(commonStates)�F�R�����X�e�C�g�̃|�C���^
// ����(camera)�F�J�����̃|�C���^
// �߂�l�F�Ȃ�
//---------------------------------------------------------------------
void Player::Draw(DirectX::CommonStates* commonStates, Camera* camera)
{
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


	pRM->GetCmoModel("Player")->Draw(
		context,
		*commonStates,
		DirectX::SimpleMath::Matrix::CreateFromQuaternion(q) * world,
		view,
		projection
	);
}

//------------------------------------------------------------------
// �T�v�F�I������
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//------------------------------------------------------------------
void Player::Finalize()
{
}

//------------------------------------------------------------------
// �T�v�F����
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//------------------------------------------------------------------
void Player::Move()
{
	// �L�[���͏����擾����
	auto keyState = InputManager::GetInstance();

	// �v���C���[�̍��W���擾
	DirectX::SimpleMath::Vector3 playerPos = DirectX::SimpleMath::Vector3::Zero;
	playerPos = GetObjectPos();

	// �����x
	float acc = ACCELERATION;

	// �t���O�����낷
	mPlayerMoveFlag = false;

	// �v���C���[�̃X�s�[�h��錾
	DirectX::SimpleMath::Vector3 playerSpeed = GetObjectSpeed();
	// �v���C���[�̃A���O����錾
	DirectX::SimpleMath::Vector3 playerAngle = GetObjectDirection();

	// �{�^�����������Ƃ�
	if (keyState->GetKeyboardState().Left)
	{
		playerSpeed.x -= acc;
		playerAngle.z += ANGLE;
		playerAngle.y += ANGLE;
		mPlayerMoveFlag = true;
	}
	if (keyState->GetKeyboardState().Right)
	{
		playerSpeed.x += acc;
		playerAngle.z -= ANGLE;
		playerAngle.y -= ANGLE;

		mPlayerMoveFlag = true;
	}
	if (keyState->GetKeyboardState().Up)
	{
		playerSpeed.y += acc;
		playerAngle.x += 0.5f;
		mPlayerMoveFlag = true;
	}
	if (keyState->GetKeyboardState().Down)
	{
		playerSpeed.y -= acc;
		playerAngle.x -= 0.5f;
		mPlayerMoveFlag = true;
	}

	// �v���C���[���ړ����Ă��Ȃ��Ƃ�
	if (!mPlayerMoveFlag)
	{
		if (playerAngle.x > 0.0f)
		{
			playerAngle.x -= ANGLE;
		}
		else if (playerAngle.x < 0.0f)
		{
			playerAngle.x += ANGLE;
		}
		if (playerAngle.z > 0.0f)
		{
			playerAngle.z -= ANGLE;
		}
		else if (playerAngle.z < 0.0f)
		{
			playerAngle.z += ANGLE;
		}
		if (playerAngle.y > 0.0f)
		{
			playerAngle.y -= ANGLE;
		}
		else if (playerAngle.y < 0.0f)
		{
			playerAngle.y += ANGLE;
		}


		//�v���C���[���~�߂�
		if (playerSpeed.x > 0.000000000f)
		{
			playerSpeed.x -= STOP_PLAYER;
		}
		else if (playerSpeed.x < 0.000000000f)
		{
			playerSpeed.x += STOP_PLAYER;
		}
		if (playerSpeed.y > 0.000000000f)
		{
			playerSpeed.y -= STOP_PLAYER;
		}
		else if (playerSpeed.y < 0.000000000f)
		{
			playerSpeed.y += STOP_PLAYER;
		}
	}


	playerAngle.Clamp(
		LIMIT_SPEED_MIN,
		LIMIT_SPEED_MAX
	);

	SetObjectDirection(playerAngle);
	SetObjectSpeed(playerSpeed);


	// �X�s�[�h�����Z����
	playerPos.x += GetObjectSpeed().x;
	playerPos.y += GetObjectSpeed().y;


	// �ŏ��l�ƍő�l�����߂�
	// todo���̒i�K�ő��x��߂��Ă���
	playerPos.Clamp(
		LIMIT_POS_MIN,
		LIMIT_POS_MAX
	);

	// �v���C���̍��W���Z�b�g����
	SetObjectPos(playerPos);
}

//------------------------------------------------------------------
// �T�v�F�_���[�W
// ���� (damage)�F�_���[�W�̒l
// �߂�l�F�Ȃ�
//------------------------------------------------------------------
void Player::Damage(int damage)
{
	int hp = GetHP();
	hp -= damage;
	SetHP(hp);
}

//------------------------------------------------------------------
// �T�v�F�e�۔���
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//------------------------------------------------------------------
void Player::Shot()
{
	// �L�[���͏����擾����
	auto keyState = DirectX::Keyboard::Get().GetState();

	++mShootIntervalTimer %= SHOT_INTERVAL;
	
	bool shootTime = mShootIntervalTimer == 0;
	if (shootTime && keyState.Space)
	{
		mpBulletManager->Shot(0,GetObjectPos(),GetObjectDirection());
	}
}

//�Q�b�^�Z�b�^-------------------------------------------------------------------
//---------------------------------------
// �T�v�F���W�̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(Vector3)�F�I�u�W�F�N�g�̍��W
//---------------------------------------
DirectX::SimpleMath::Vector3 Player::GetObjectPos() const
{
	return HeartObject::GetObjectPos();
}
//---------------------------------------
// �T�v�F���W�̃Z�b�^�[
// ����(pos)�F�I�u�W�F�N�g�̍��W
// �߂�l�F�Ȃ�
//---------------------------------------
void Player::SetObjectPos(const DirectX::SimpleMath::Vector3& pos)
{
	HeartObject::SetObjectPos(pos);
}

//---------------------------------------
// �T�v�F�����̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(Vector3)�F�I�u�W�F�N�g�̍��W
//---------------------------------------
DirectX::SimpleMath::Vector3 Player::GetObjectDirection() const
{
	return HeartObject::GetObjectDirection();
}
//---------------------------------------
// �T�v�F�����̃Z�b�^�[
// ����(direction)�F�I�u�W�F�N�g�̌���
// �߂�l�F�Ȃ�
//---------------------------------------
void Player::SetObjectDirection(const DirectX::SimpleMath::Vector3& direction)
{
	HeartObject::SetObjectDirection(direction);
}

//---------------------------------------
// �T�v�F�����̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(Vector3)�F�I�u�W�F�N�g�̑���
//---------------------------------------
DirectX::SimpleMath::Vector3 Player::GetObjectSpeed() const
{
	return HeartObject::GetObjectSpeed();
}
//---------------------------------------
// �T�v�F�����̃Z�b�^�[
// ����(speed)�F�I�u�W�F�N�g�̑���
// �߂�l�F�Ȃ�
//---------------------------------------
void Player::SetObjectSpeed(const DirectX::SimpleMath::Vector3& speed)
{
	HeartObject::SetObjectSpeed(speed);
}

//---------------------------------------
// �T�v�F�g�p��Ԃ̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(bool)�F�I�u�W�F�N�g�̎g�p���
//---------------------------------------
bool Player::GetActive() const
{
	return HeartObject::GetActive();
}
//---------------------------------------
// �T�v�F�g�p��Ԃ̃Z�b�^�[
// ����(active)�F�I�u�W�F�N�g�̎g�p���
// �߂�l�F�Ȃ�
//---------------------------------------
void Player::SetActive(const bool& active)
{
	HeartObject::SetActive(active);
}

//---------------------------------------
// �T�v�FHP�̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(int)�F�I�u�W�F�N�g��HP
//---------------------------------------
int Player::GetHP() const
{
	return HeartObject::GetHP();
}
//---------------------------------------
// �T�v�FHP�̃Z�b�^�[
// ����(hp)�F�I�u�W�F�N�g��HP
// �߂�l�F�Ȃ�
//---------------------------------------
void Player::SetHP(const int& hp)
{
	HeartObject::SetHP(hp);
}
