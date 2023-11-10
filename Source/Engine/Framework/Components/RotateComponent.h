#pragma once

#include "Component.h"

namespace nc
{
	class RotateComponent : public Component
	{
	public:
		CLASS_DECLARATION(RotateComponent)

		void Update(float dt) override;

		void ProcessGui();

	public:
		glm::vec3 euler{ 0 };
	};
}