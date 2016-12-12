#include "Culling.h"
#include "Object3D.h"
#include "Camera.h"
#include "CollisionManager.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX::SimpleMath;

Culling::Culling()
{
}


Culling::~Culling()
{
}

bool Culling::InView(Box& box,Camera* camera,int required,float sx, float sy)
{
	int num = 0;
	for (int i = 0; i < 8; i++)
	{
		//�r���[�|�[�g�s����v�Z
		Matrix trans = Matrix::CreateTranslation(box.point[i]);
		Matrix world = Matrix::Identity;
		Matrix view = camera->GetView();
		Matrix proj = camera->GetProj();

		Matrix result = trans * world * view * proj;

		result._41 /= result._44;
		result._42 /= result._44;
		result._43 /= result._44;

		//�w�肳�ꂽ�r���[�|�[�g�Ȃ��ɂ��邩�ǂ���
		if (result._41 > -sx && result._41 < sx
			&& result._42 > -sy && result._42 < sy
			&& result._43 >0 && result._43 < 1)
		{
			num++;
		}
	}

	if (num >= required)
		return true;
	else
		return false;
}
