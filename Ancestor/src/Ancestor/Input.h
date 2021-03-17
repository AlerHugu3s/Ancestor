#pragma once

#include "Ancestor/Core.h"

namespace Ancestor {

	class ANCESTOR_API Input 
	{
	public:
		static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		static bool IsMouseButtonPressed(int keycode) { return s_Instance->IsMouseButtonPressedImpl(keycode); }
		static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		static float GetMouseX() { return s_Instance->GetMousePosXImpl(); }
		static float GetMouseY() { return s_Instance->GetMousePosYImpl(); }
		
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int keycode) = 0;
		virtual std::pair<float,float> GetMousePositionImpl() = 0;
		virtual float GetMousePosXImpl() = 0;
		virtual float GetMousePosYImpl() = 0;
	private:
		static Input* s_Instance;
	};
}