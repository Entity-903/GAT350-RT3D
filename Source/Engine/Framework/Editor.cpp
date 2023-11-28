#include "Editor.h"

#include "Components/CameraComponent.h"
#include "Scene.h"

namespace nc
{
	void Editor::Update()
	{
		if (ImGui::IsKeyPressed(ImGuiKey_GraveAccent))
		{
			active = !active;
		}
	}

	void nc::Editor::ProcessGui(Scene* scene)
	{
		if (!active) return;

		// Show resources
		ImGui::Begin("Resources");
		auto resources = GET_RESOURCES(Resource);
		for (auto& resource : resources)
		{
			if (ImGui::Selectable(resource->name.c_str(), resource.get() == m_selected))
			{
				m_selected = resource.get();
			}
		}
		ImGui::End();

		// Show scene
		ImGui::Begin("Scene");
		scene->ProcessGui();
		ImGui::Separator();
		// Show actors
		ImGui::BeginChild("Actors");

		// Actor Controls
		if (ImGui::BeginPopupContextWindow())
		{
			auto cameras = scene->GetComponents<CameraComponent>();
			auto camera = (!cameras.empty()) ? cameras[0] : nullptr;

			if (ImGui::MenuItem("Create Empty"))
			{
				auto actor = CREATE_CLASS(Actor);
				actor->name = StringUtils::CreateUnique(actor->GetClassName());
				actor->Initialize();

				selectedObject = actor.get();
				scene->Add(std::move(actor));
			}

			if (ImGui::MenuItem("Create Sphere"))
			{
				auto actor = CREATE_CLASS_BASE(Actor, "Sphere");
				actor->name = StringUtils::CreateUnique(actor->name);
				if (camera != nullptr)
				{
					actor->transform.position = camera->m_owner->transform.position + (camera->m_owner->transform.Forward() * 3.0f);
				}
				actor->Initialize();

				selectedObject = actor.get();
				scene->Add(std::move(actor));
			}

			if (ImGui::MenuItem("Create Cube"))
			{
				auto actor = CREATE_CLASS_BASE(Actor, "Cube");
				actor->name = StringUtils::CreateUnique(actor->name);
				if (camera != nullptr)
				{
					actor->transform.position = camera->m_owner->transform.position + (camera->m_owner->transform.Forward() * 3.0f);
				}
				actor->Initialize();

				selectedObject = actor.get();
				scene->Add(std::move(actor));
			}

			if (ImGui::MenuItem("Create Camera"))
			{
				auto actor = CREATE_CLASS_BASE(Actor, "Camera");
				actor->name = StringUtils::CreateUnique(actor->name);
				if (camera != nullptr)
				{
					actor->transform.position = camera->m_owner->transform.position + (camera->m_owner->transform.Forward() * 3.0f);
				}
				actor->Initialize();

				selectedObject = actor.get();
				scene->Add(std::move(actor));
			}

			if (ImGui::MenuItem("Create Light"))
			{
				auto actor = CREATE_CLASS_BASE(Actor, "Light");
				actor->name = StringUtils::CreateUnique(actor->name);
				if (camera != nullptr)
				{
					actor->transform.position = camera->m_owner->transform.position + (camera->m_owner->transform.Forward() * 3.0f);
				}
				actor->Initialize();

				this->selectedObject = actor.get();
				scene->Add(std::move(actor));
			}

			ImGui::EndPopup();
		}

		for (auto& actor : scene->m_actors)
		{
			if (ImGui::Selectable(actor->name.c_str(), actor.get() == m_selected))
			{
				m_selected = actor.get();
			}
		}
		ImGui::EndChild();
		ImGui::End();

		// Show inspector
		ImGui::Begin("Inspector");
		if (m_selected)
		{
			m_selected->ProcessGui();
			// delete selected actor
			if (ImGui::IsKeyPressed(ImGuiKey_Delete))
			{
				auto actor = dynamic_cast<Actor*>(m_selected);
				if (actor)
				{
					scene->Remove(actor);
					m_selected = nullptr;
				}
			}
		}

		ImGui::End();
	}

}
