#include "Renderer/Model/Model.h"

namespace Renderer
{
	Model::Model() 
		: m_GeometryId(INVALID_GEOMETRY_ID) 
	{}

	Model::~Model()
	{
		m_GeometryId = INVALID_GEOMETRY_ID;
	}
}
