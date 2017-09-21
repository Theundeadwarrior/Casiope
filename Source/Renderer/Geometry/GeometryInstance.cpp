#include "Renderer/Geometry/GeometryInstance.h"


namespace Renderer
{
	GeometryInstance::GeometryInstance(GraphicsCore::Geometry * geometry)
		: m_GeometryId(geometry) 
	{
	
	}

	void GeometryInstance::SetGeometry(GraphicsCore::Geometry * geometry)
	{
		m_GeometryId = geometry;
	}
}
