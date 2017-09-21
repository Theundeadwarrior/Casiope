#include "Renderer/Mesh/Mesh.h"

namespace Renderer
{
	Mesh::Mesh() 
		: m_GeometryId(INVALID_GEOMETRY_ID) 
	{}

	Mesh::~Mesh()
	{
		m_GeometryId = INVALID_GEOMETRY_ID;
	}
}
