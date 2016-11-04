#include "LandShapeData.h"
#include <fstream>

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

unique_ptr<LandShapeData> LandShapeData::CreateFromMDL(const char * meshData)
{
	const void* head = meshData;
		
	unique_ptr<LandShapeData> landShape(new LandShapeData());

	const UINT* node = static_cast<const UINT*>(head);
	head = node + 1;
	UINT numNode = *node;

	const NodeInfo* nodeInfoArray = static_cast<const NodeInfo*>(head);
	head = nodeInfoArray + numNode;

	int mesh = 0;
	landShape->indices_.clear();
	vector<vector<VERTEX_LANDSHAPE>> vertexArray;
	vector<vector<USHORT>> indexArray;
	for (UINT i = 0; i < numNode; i++)
	{
		const NodeInfo* nodeInfo = &nodeInfoArray[i];

		vector<VERTEX_LANDSHAPE> va;
		vector<USHORT> ia;

		vertexArray.push_back(va);
		indexArray.push_back(ia);

		if (nodeInfo->kind_ == 1)
		{
			const UINT* numVertex = static_cast<const UINT*>(head);
			head = numVertex + 1;
			UINT vertex = *numVertex;
			vertexArray[i].reserve(vertex);

			size_t vbBytes = sizeof(VERTEX_LIFE)*vertex;
			const VERTEX_LIFE*	nodeVertexArray = static_cast<const VERTEX_LIFE*>(head);
			head = nodeVertexArray + vertex;

			for (UINT j = 0; j < vertex; j++)
			{
				const VERTEX_LIFE* vertex = &nodeVertexArray[j];
				VERTEX_LANDSHAPE vertexLandShape;
				vertexLandShape.pos_ = vertex->pos_;
				vertexLandShape.normal_ = vertex->normal_;
				vertexArray[i].push_back(vertexLandShape);
			}

			const UINT* indices = static_cast<const UINT*>(head);
			head = indices + 1;
			UINT numIndices = *indices;
			indexArray[i].reserve(numIndices);

			size_t ibBytes = sizeof(USHORT)* numIndices;
			const USHORT* nodeIndexArray = static_cast<const USHORT*>(head);
			head = numIndices + nodeIndexArray;
			
			for (UINT j = 0; j < numIndices; j++)
			{
				const USHORT* index = &nodeIndexArray[j];
				indexArray[i].push_back(*index);
			}
		}

		UpdateNodeMatrices(0, nodeInfoArray, nullptr, vertexArray);

		landShape->vertices_.clear();
		landShape->indices_.clear();
		int vertex_count = 0;
		for (UINT i = 0; i < numNode; i++)
		{
			for (auto it = indexArray[i].begin(); it != indexArray[i].end(); it++)
			{
				*it += vertex_count;
			}
			vertex_count += vertexArray[i].size();

			landShape->vertices_.insert(landShape->vertices_.end(), vertexArray[i].begin(), vertexArray[i].end());
			landShape->indices_.insert(landShape->indices_.end(), indexArray[i].begin(), indexArray[i].end());
		}
	}

	return landShape;
}

unique_ptr<LandShapeData> LandShapeData::CreateFromMDL(const wchar_t * szFileName)
{
	ifstream ifs;
	unique_ptr<char[]> data;

	ifs.open(szFileName, ios::in | ios::binary);

	assert(ifs&&"CreateFromMDL Error:Failed to Open MDL.");

	ifs.seekg(0, fstream::end);
	streamoff eofPos = ifs.tellg();
	ifs.clear();
	ifs.seekg(0, fstream::beg);
	streamoff begPos = ifs.tellg();
	streamoff size = eofPos - begPos;

	data.reset(new char[(UINT)size]);

	ifs.read(data.get(), size);

	ifs.close();

	OutputDebugStringW(szFileName);
	OutputDebugStringW(L"\n");

	auto model = CreateFromMDL(data.get());

	model->name = szFileName;

	return model;
}

void LandShapeData::UpdateNodeMatrices(int index, const NodeInfo * nodeInfo_array, DirectX::SimpleMath::Matrix * parentMatrix, std::vector<std::vector<VERTEX_LANDSHAPE>>& vertexArray)
{
	const NodeInfo* nodeInfo = &nodeInfo_array[index];

	Matrix world;
	Matrix rotate = Matrix::CreateFromQuaternion(nodeInfo->rotation_);
	Matrix trans = Matrix::CreateTranslation(nodeInfo->translation_);
		
	world = rotate * trans;
	if (parentMatrix)
	{
		world = world * (*parentMatrix);
	}

	if (nodeInfo->kind_ == 1)
	{
		for (auto it = vertexArray[index].begin(); it != vertexArray[index].end(); it++)
		{
			it->pos_ = Vector3::Transform(it->pos_, world);
			it->normal_ = Vector3::TransformNormal(it->normal_, world);

			char str[256];

			sprintf_s(str, "(%.3f,%.3f, %.3f)\n", it->pos_.x, it->pos_.y, it->pos_.z);

			OutputDebugStringA(str);
		}
	}

	if (nodeInfo->sibling_ > 0)
	{
		UpdateNodeMatrices(nodeInfo->sibling_, nodeInfo_array, parentMatrix, vertexArray);
	}
	if (nodeInfo->child_ > 0)
	{
		UpdateNodeMatrices(nodeInfo->sibling_, nodeInfo_array, &world, vertexArray);
	}
}

