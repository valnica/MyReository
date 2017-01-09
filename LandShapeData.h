//////////////////////////////////////////////
// Name : LandShapeData
//
// Author : 山田 聖弥
//
// Date : 2017/1/9
//////////////////////////////////////////////
#pragma once

#include <vector>
#include <memory>
#include <SimpleMath.h>

//////////////////////////////////////////////
// Class Name : LandShapeData
//
// Over View : 地形読み込み用のクラス
//////////////////////////////////////////////
class LandShapeData
{
public:
	friend class LandShape;
	struct VERTEX_LANDSHAPE
	{
		DirectX::SimpleMath::Vector3 pos_;
		DirectX::SimpleMath::Vector3 normal_;
	};

	struct VERTEX_LIFE
	{
		DirectX::SimpleMath::Vector3 pos_;
		DirectX::SimpleMath::Vector3 normal_;
		DirectX::SimpleMath::Vector2 uv_;
	};

	struct NodeInfo
	{
		struct Material
		{
			char name_[32];
			DirectX::SimpleMath::Vector3 ambient_;
			DirectX::SimpleMath::Vector3 diffuse_;
			DirectX::SimpleMath::Vector3 specular_;
			DirectX::SimpleMath::Vector3 emissive_;
			float opacity_;
			float shininess_;
			float reflectivity_;
		};

		int kind_;
		char name_[32];
		int sibling_;
		int child_;

		DirectX::SimpleMath::Vector3 translation_;
		DirectX::SimpleMath::Quaternion rotation_;

		char textureNameA[32];
		char textureNameB[32];
		char textureNameC[32];

		Material material_;
	};

	std::wstring name;
	std::vector<VERTEX_LANDSHAPE> vertices_;
	std::vector<USHORT> indices_;

	//読み込み
	static std::unique_ptr<LandShapeData> CreateFromMDL(const char* meshData);
	static std::unique_ptr<LandShapeData> CreateFromMDL(const wchar_t* szFileName);
	static void	UpdateNodeMatrices(int index, const NodeInfo* nodeInfo_array, DirectX::SimpleMath::Matrix* parentMatrix, std::vector<std::vector<VERTEX_LANDSHAPE>>& vertexArray);
};
