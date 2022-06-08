#include "pch.h"
#include "Hatch.h"

Hatch::Hatch()
{
}

Hatch::~Hatch()
{
}

void Hatch::Initialize()
{
}

void Hatch::Update()
{
}

void Hatch::Draw(DirectX::CommonStates* commonStates, Camera* camera)
{
}

void Hatch::Finalize()
{
}

void Hatch::Move()
{
}

DirectX::SimpleMath::Vector3 Hatch::GetObjectPos() const
{
	return DirectX::SimpleMath::Vector3();
}

void Hatch::SetObjectPos(const DirectX::SimpleMath::Vector3& pos)
{
}

DirectX::SimpleMath::Vector3 Hatch::GetObjectDirection() const
{
	return DirectX::SimpleMath::Vector3();
}

void Hatch::SetObjectDirection(const DirectX::SimpleMath::Vector3& direction)
{
}

DirectX::SimpleMath::Vector3 Hatch::GetObjectSpeed() const
{
	return DirectX::SimpleMath::Vector3();
}

void Hatch::SetObjectSpeed(const DirectX::SimpleMath::Vector3& speed)
{
}

bool Hatch::GetActive() const
{
	return false;
}

void Hatch::SetActive(const bool& active)
{
}

void Hatch::GetIsOpen() const
{
}
