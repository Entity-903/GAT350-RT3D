#include "World06.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"

#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtx/color_space.hpp>

#define INTERLEAVE

namespace nc
{
    bool World06::Initialize()
    {
        m_scene = std::make_unique<Scene>();
        m_scene->Load("scenes/scene_framebuffer.json");
        m_scene->Initialize();

        auto texture = std::make_shared<Texture>();
        texture->CreateTexture(1024, 1024);
        ADD_RESOURCE(Texture, "fb_texture", texture);

        auto framebuffer = std::make_shared<Framebuffer>();
        framebuffer->CreateFramebuffer(texture);
        ADD_RESOURCE(Framebuffer, "fb", framebuffer);

        auto material = GET_RESOURCE(Material, "materials/postprocess.mtrl");
        if (material != nullptr)
        {
            material->albedoTexture = texture;
        }

        {
            auto actor = CREATE_CLASS(Actor);
            actor->name = "camera1";
            actor->transform.position = glm::vec3{ 0, 0, 3 };
            actor->transform.rotation = glm::radians(glm::vec3{ 0, 180, 0 });

            auto cameraComponent = CREATE_CLASS(CameraComponent);
            cameraComponent->SetPerspective(70.0f, ENGINE.GetSystem<Renderer>()->GetWidth() / (float)ENGINE.GetSystem<Renderer>()->GetHeight(), 0.1f, 100.0f);
            actor->AddComponent(std::move(cameraComponent));

            auto cameraController = CREATE_CLASS(CameraController);
            cameraController->speed = 5;
            cameraController->sensitivity = 0.5f;
            cameraController->m_owner = actor.get();
            cameraController->Initialize();
            actor->AddComponent(std::move(cameraController));

            m_scene->Add(std::move(actor));
        }

        return true;
    }

    void World06::Shutdown()
    {
    }

    void World06::Update(float dt)
    {
        ENGINE.GetSystem<Gui>()->BeginFrame();

        m_scene->Update(dt);
        m_scene->ProcessGui();

        auto program = GET_RESOURCE(Program, "Shaders/postprocess.prog");
        if (program != nullptr)
        {
            program->Use();

            ImGui::Begin("Post Processing");
            ImGui::SliderFloat("Blend", &m_blend, 0, 1);
            bool effect = m_params & INVERT_MASK;
            if (ImGui::Checkbox("Invert", &effect))
            {
                if (effect)
                {
                    m_params |= INVERT_MASK;
                }
                else
                {
                    m_params &= ~INVERT_MASK;
                }
            }

            effect = m_params & GRAYSCALE_MASK;
            if (ImGui::Checkbox("Grayscale", &effect))
            {
                if (effect)
                {
                    m_params |= GRAYSCALE_MASK;
                }
                else
                {
                    m_params &= ~GRAYSCALE_MASK;
                }
            }

            effect = m_params & COLORTINT_MASK;
            if (ImGui::Checkbox("Colortint", &effect))
            {
                if (effect)
                {
                    m_params |= COLORTINT_MASK;
                }
                else
                {
                    m_params &= ~COLORTINT_MASK;
                }
            }



            ImGui::ColorEdit3("Colortint Value", glm::value_ptr(m_colorTint));
            ImGui::End();

            program->SetUniform("blend", m_blend);
            program->SetUniform("params", m_params);
            program->SetUniform("tint", m_colorTint);

        }

        ENGINE.GetSystem<Gui>()->EndFrame();
    }

    void World06::Draw(Renderer& renderer)
    {
        // ** PASS 1 **
        m_scene->GetActorByName("postprocess")->active = false;

        auto framebuffer = GET_RESOURCE(Framebuffer, "fb");
        renderer.SetViewport(framebuffer->GetSize().x, framebuffer->GetSize().y);
        framebuffer->Bind();

        renderer.BeginFrame(glm::vec3(0, 0, 0));
        m_scene->Draw(renderer);

        framebuffer->Unbind();

        // ** PASS 2 **
        m_scene->GetActorByName("postprocess")->active = true;

        renderer.ResetViewport();
        renderer.BeginFrame();
        m_scene->GetActorByName("postprocess")->Draw(renderer);

        // post-render
        ENGINE.GetSystem<Gui>()->Draw();
        renderer.EndFrame();
    }
}
