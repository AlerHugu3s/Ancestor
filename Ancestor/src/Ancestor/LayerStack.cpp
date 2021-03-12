#include "acpch.h"
#include "LayerStack.h"


namespace Ancestor {

	Ancestor::LayerStack::LayerStack()
	{
		m_LayerInsert = m_Layers.begin();
	}

	Ancestor::LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
			delete layer;
	}

	void Ancestor::LayerStack::PushLayer(Layer* layer)
	{
		m_LayerInsert = m_Layers.emplace(m_LayerInsert,layer);
	}

	void Ancestor::LayerStack::PushOverLayer(Layer* layer)
	{
		m_Layers.emplace_back(layer);
	}

	void Ancestor::LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(),layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayerInsert--;
		}
			
	}

	void Ancestor::LayerStack::PopOverLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
			m_Layers.erase(it);
	}

}