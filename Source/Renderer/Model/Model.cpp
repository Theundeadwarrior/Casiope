#include "Model.h"

#include "GraphicsCore/Mesh/Mesh.h"
#include "Renderer/Material/Material.h"

namespace Renderer
{
	Model::Model()
	{

	}

	Model::Model(const GraphicsCore::Mesh* mesh, const IMaterial* material)
	{
		m_Mesh = mesh;
	}

	Model::~Model()
	{

	}
}
