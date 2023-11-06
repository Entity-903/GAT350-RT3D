#include "World05.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"

#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtx/color_space.hpp>

#define INTERLEAVE

namespace nc
{
    bool World05::Initialize()
    {
        m_scene = std::make_unique<Scene>();
        m_scene->Load("scenes/scene.json");
        m_scene->Initialize();

        {
            auto actor = CREATE_CLASS(Actor);
            actor->name = "camera1";
            actor->transform.position = glm::vec3{ 0, 0, 3 };
            actor->transform.rotation = glm::vec3{ 0, 180, 0 };

            auto cameraComponent = CREATE_CLASS(CameraComponent);
            cameraComponent->SetPerspective(70.0f, ENGINE.GetSystem<Renderer>()->GetWidth() / (float)ENGINE.GetSystem<Renderer>()->GetHeight(), 0.1f, 100.0f);
            actor->AddComponent(std::move(cameraComponent));

            m_scene->Add(std::move(actor));
        }

        return true;
    }

    void World05::Shutdown()
    {
    }

    void World05::Update(float dt)
    {
        ENGINE.GetSystem<Gui>()->BeginFrame();

        m_scene->Update(dt);
        m_scene->ProcessGui();

        auto camera = m_scene->GetActorByName<Actor>("camera1");

        camera->transform.position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_A) ? m_speed * -dt : 0;
        camera->transform.position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_D) ? m_speed * dt : 0;
        camera->transform.position.y += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_W) ? m_speed * dt : 0;
        camera->transform.position.y += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_S) ? m_speed * -dt : 0;
        camera->transform.position.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_Q) ? m_speed * dt : 0;
        camera->transform.position.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_E) ? m_speed * -dt : 0;

        camera->transform.rotation.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_I) ? dt * 90 : 0;
        camera->transform.rotation.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_K) ? -dt * 90 : 0;
        camera->transform.rotation.y += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_J) ? dt * 90 : 0;
        camera->transform.rotation.y += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_L) ? -dt * 90 : 0;
        camera->transform.rotation.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_U) ? dt * 90 : 0;
        camera->transform.rotation.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_O) ? -dt * 90 : 0;

        m_time += dt;

        auto actor = m_scene->GetActorByName<Actor>("actor1");

        auto material = actor->GetComponent<ModelComponent>()->model->GetMaterial();

        material->ProcessGui();
        material->Bind();

        material = GET_RESOURCE(Material, "materials/refraction.mtrl");
        if (material)
        {
            ImGui::Begin("Refraction");

            //m_refraction = 1.0f + std::fabs(std::sin(m_time * 0.1f));

            ImGui::DragFloat("IOR", &m_refraction, 0.01f, 1, 3);
            auto program = material->GetProgram();
            program->Use();
            program->SetUniform("ior", m_refraction);

            ImGui::End();
        }

        material->GetProgram()->SetUniform("ambientLight", ambientLight);

        ENGINE.GetSystem<Gui>()->EndFrame();
    }

    void World05::Draw(Renderer& renderer)
    {
        // pre-render
        renderer.BeginFrame();

        // render
        // 
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // for wire frame
        m_scene->Draw(renderer);
        ENGINE.GetSystem<Gui>()->Draw();

        // post-render
        renderer.EndFrame();
    }
}
