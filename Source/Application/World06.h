#pragma once
#include "Framework/World.h"
#include "Renderer/Renderer.h"
#include "Core/Math/Transform.h"
#include <vector>

//#define POINT 0

namespace nc
{

	class World06 : public World
	{
	public:
		const uint32_t INVERT_MASK    = 1;
		const uint32_t GRAYSCALE_MASK = 2;
		const uint32_t COLORTINT_MASK = 4;

	public:
		bool Initialize() override;
		void Shutdown() override;
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

	private:
		//float m_time = 0;
		uint32_t m_params = 0;
		glm::vec3 m_colorTint = glm::vec3(0);

		float m_blend = 1.0f;
		glm::vec3 ambientLight{0.2, 0.2, 0.2};
	};
}