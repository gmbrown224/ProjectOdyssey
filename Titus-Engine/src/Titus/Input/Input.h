#pragma once

#include "Titus/Core.h"

// TODO: Platform specific input is determined at compile time, so polymorphism is not
// really necessary here. making implementations for each platform and including based
// on preprocessor definitions would be better.

namespace Titus
{
	class TITUS_API Input
	{
	public:
		static bool IsKeyPressed(int keycode) { return s_Istance->IsKeyPressedImpl(keycode); }

		static bool IsMouseButtonPressed(int button) { return s_Istance->IsMouseButtonPressedImpl(button); }
		static std::pair<float, float> GetMousePosition() { return s_Istance->GetMousePositionImpl(); }
		static float GetMouseX() { return s_Istance->GetMouseXImpl(); }
		static float GetMouseY() { return s_Istance->GetMouseYImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;

		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:
		static Input* s_Istance;
	};
}