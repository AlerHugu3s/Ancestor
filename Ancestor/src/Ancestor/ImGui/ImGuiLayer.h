#pragma once

#include "Ancestor/Layer.h"
#include "Ancestor/Events/MouseEvent.h"
#include "Ancestor/Events/KeyEvent.h"
#include "Ancestor/Events/ApplicationEvent.h"

namespace Ancestor {
	class ANCESTOR_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& event) override;
	private:
		float m_Time = 0.0f;

		bool MousePressedCallback(MouseButtonPressedEvent& e);
		bool MouseMoveCallback(MouseMoveEvent& e);
		bool MouseReleasedCallback(MouseButtonReleasedEvent& e);
		bool MouseScrolledCallback(MouseScrolledEvent& e);
		bool KeyPressedCallback(KeyPressedEvent& e);
		bool KeyReleasedCallback(KeyReleasedEvent& e);
		bool KeyTypeCallback(KeyTypedEvent& e);
		bool WindowResizeCallback(WindowResizeEvent& e);
	};
}
