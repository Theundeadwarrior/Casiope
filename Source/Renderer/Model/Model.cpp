#include "Model.h"

#include "GraphicsCore/Mesh/Mesh.h"
#include "Renderer/Material/Material.h"

namespace Renderer
{
	Model::Model(GraphicsCore::Mesh* mesh, IMaterial* material)
	{
		m_Mesh = mesh;
		m_Material = material;
	}
}
