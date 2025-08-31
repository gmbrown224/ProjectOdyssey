#include "TEpch.h"

#include "Layer.h"

namespace Titus
{
	Layer::Layer(const std::string& name)
		: m_DebugName(name) { }

	Layer::~Layer() { }
}