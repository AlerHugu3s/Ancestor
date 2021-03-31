#pragma once

#include "Ancestor/Core.h"
#include "Ancestor/Events/Event.h"
#include "Ancestor/Core/Timestep.h"

namespace Ancestor{
	class ANCESTOR_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach(){}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	private:
		std::string m_DebugName;
	};
}

