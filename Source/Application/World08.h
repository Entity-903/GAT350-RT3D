#pragma once
#include "Framework/World.h"
#include "Renderer/Renderer.h"
#include "Core/Math/Transform.h"
#include <vector>

namespace nc
{

	class World08 : public World
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
		int celLevels = 5;
		float celSpecularCutoff = 0.3f;

		glm::vec3 ambientLight{0.2, 0.2, 0.2};
	};
}