#pragma once
#include "Component.h"
#include "Renderer/Program.h"
#include "Framework/Actor.h"

namespace nc
{
	class LightComponent : public Component
	{
	public:
		CLASS_DECLARATION(LightComponent)

		bool Initialize() override;
		void Update(float dt) override;
		void SetProgram(const res_t<Program> program, const std::string& name);

		void ProcessGui() override;

		glm::mat4 GetShadowMatrix();

	public:
		enum lightType
		{
			Point,
			Directional,
			Spot
		};

		lightType lightType = lightType::Point;
		glm::vec3 color{ 1 };
		float intensity = 1;
		float range = 20;
		float innerAngle = 20;
		float outerAngle = 30;

		bool castShadow = false;
		float shadowSize = 10;
		float shadowBias = 0.005f;
	};
}
