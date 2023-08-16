#include "Entity.h"
#include "../../core/Memory.h"

Matrix3x4* BaseEntity::GetBoneMatrix()
{
	static Matrix3x4 matrix[256];

	if (this->SetupBones(matrix, 256, 256, memory->globalVars->currentTime))
		return matrix;
	else
		return nullptr;
}

Vector BaseEntity::GetBonePosition(int bone)
{
	Matrix3x4 matrix[256];

	if (this->SetupBones(matrix, 256, 256, memory->globalVars->currentTime))
		return matrix[bone].at(3);
	else
		return { };
}
