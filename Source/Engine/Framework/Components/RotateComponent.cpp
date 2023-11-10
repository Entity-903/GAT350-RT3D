#include "RotateComponent.h"

#include <Core/Math/Transform.h>
#include "Framework/Actor.h"

namespace nc
{
	CLASS_DEFINITION(RotateComponent)

	void RotateComponent::Update(float dt)
	{
		glm::quat rotation = EulerToQuaternion(euler * dt);
		m_owner->transform.rotation = m_owner->transform.rotation * rotation;
		m_owner->transform.euler += euler * dt;
	}

	void RotateComponent::ProcessGui()
	{
		ImGui::DragFloat3("EulerRotate", glm::value_ptr(euler), 0.01f);
	}

	void RotateComponent::Read(const nc::json_t& value)
	{
		// read json file
		READ_NAME_DATA(value, "rotation", euler);

	}
}