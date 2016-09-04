#include "Renderer/Geometry/GeometryInstance.h"


namespace Renderer
{
	GeometryInstance::GeometryInstance()
		: m_Geometry(nullptr)
	{
	}
	GeometryInstance::GeometryInstance(GraphicsCore::Geometry * geometry)
		: m_Geometry(geometry) 
	{
	
	}

	void GeometryInstance::SetGeometry(GraphicsCore::Geometry * geometry)
	{
		m_Geometry = geometry;
	}
}
