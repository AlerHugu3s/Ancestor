#pragma once

#include "Ancestor/Input.h"

namespace Ancestor {
	class WindowsInput : public Input
	{
		protected:
			virtual bool IsKeyPressedImpl(int keycode) override;
			virtual bool IsMouseButtonPressedImpl(int keycode) override;
			virtual std::pair<float, float> GetMousePositionImpl() override;
			virtual float GetMousePosXImpl() override;
			virtual float GetMousePosYImpl() override;
	};
}

