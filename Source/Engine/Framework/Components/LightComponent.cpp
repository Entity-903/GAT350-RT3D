#include "LightComponent.h"

namespace nc
{
	CLASS_DEFINITION(LightComponent)

	bool LightComponent::Initialize()
	{
		return true;
	}

	void LightComponent::Update(float dt)
	{
	}

	void LightComponent::SetProgram(const res_t<Program> program, const std::string& name)
	{
		program->SetUniform(name + ".type", lightType);
		program->SetUniform(name + ".position", m_owner->transform.position);
		program->SetUniform(name + ".direction", m_owner->transform.Forward());
		program->SetUniform(name + ".color", color);
		program->SetUniform(name + ".intensity", intensity);
		program->SetUniform(name + ".range", range);
		program->SetUniform(name + ".innerAngle", glm::radians(innerAngle));
		program->SetUniform(name + ".outerAngle", glm::radians(outerAngle));

		if (castShadow)
		{
			glm::mat4 bias = glm::mat4(
				glm::vec4(0.5f, 0.0f, 0.0f, 0.0f),
				glm::vec4(0.0f, 0.5f, 0.0f, 0.0f),
				glm::vec4(0.0f, 0.0f, 0.5f, 0.0f),
				glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));

			program->SetUniform("shadowVP", bias * GetShadowMatrix());
			program->SetUniform("shadowBias", shadowBias);
		}
	}

	void LightComponent::ProcessGui()
	{
		const char* types[] = { "Point", "Directional", "Spot" };
		ImGui::Combo("Type", (int*)(&lightType), types, 3);

		if (lightType == Spot)
		{
			ImGui::DragFloat("Inner Angle", &innerAngle, 1, 0, outerAngle);
			ImGui::DragFloat("Outer Angle", &outerAngle, 1, innerAngle, 90);
		}

		ImGui::ColorEdit3("Color", glm::value_ptr(color));
		ImGui::DragFloat("Intensity", &intensity, 0.1f, 0, 10);
		if (lightType != Directional) ImGui::DragFloat("Range", &range, 0.1f, 0.1f, 50);

		ImGui::Checkbox("Cast Shadow", &castShadow);
		if (castShadow)
		{
			ImGui::DragFloat("Shadow Size", &shadowSize, 0.1f, 1, 60);
			ImGui::DragFloat("Shadow Bias", &shadowBias, 0.001f, 0, 0.5f);
		}
	}

	glm::mat4 LightComponent::GetShadowMatrix()
	{
		glm::mat4 projection = glm::ortho(-shadowSize * 0.5f, shadowSize * 0.5f, -shadowSize * 0.5f, shadowSize * 0.5f, 0.1f, 50.0f);
		glm::mat4 view = glm::lookAt(m_owner->transform.position, m_owner->transform.position + m_owner->transform.Forward(), m_owner->transform.Up());

		return projection * view;
	}

	void LightComponent::Read(const nc::json_t& value)
	{
		// read json file
		std::string type = "";

		READ_NAME_DATA(value, "lightType", type);

		if (StringUtils::IsEqualIgnoreCase(type, "point"))
		{
			lightType = lightType::Point;
		}
		else if (StringUtils::IsEqualIgnoreCase(type, "directional"))
		{
			lightType = lightType::Directional;
		}
		else if (StringUtils::IsEqualIgnoreCase(type, "spot"))
		{
			lightType = lightType::Spot;
		}

		READ_DATA(value, color);
		READ_DATA(value, intensity);
		READ_DATA(value, range);
		READ_DATA(value, innerAngle);
		READ_DATA(value, outerAngle);

		READ_DATA(value, castShadow);
	}
}