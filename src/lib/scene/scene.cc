#include "src/lib/scene/scene.h"

#include "src/lib/scene/components.h"
#include "src/lib/scene/entity.h"
#include "src/lib/renderer/renderer2D.h"

#include <glm/glm.hpp>

namespace majkt {

    static void DoMath(const glm::mat4& transform)
	{

	}

	static void OnTransformConstruct(entt::registry& registry, entt::entity entity)
	{

	}

	Scene::Scene()
	{
#if ENTT_EXAMPLE_CODE
		entt::entity entity = registry_.create();
		registry_.emplace<TransformComponent>(entity, glm::mat4(1.0f));

		registry_.on_construct<TransformComponent>().connect<&OnTransformConstruct>();


		if (registry_.has<TransformComponent>(entity))
			TransformComponent& transform = registry_.get<TransformComponent>(entity);


		auto view = registry_.view<TransformComponent>();
		for (auto entity : view)
		{
			TransformComponent& transform = view.get<TransformComponent>(entity);
		}

		auto group = registry_.group<TransformComponent>(entt::get<MeshComponent>);
		for (auto entity : group)
		{
			auto&[transform, mesh] = group.get<TransformComponent, MeshComponent>(entity);
		}
#endif
	}

	Scene::~Scene()
	{
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { registry_.create(), this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;
		return entity;
	}

	void Scene::OnUpdate(Timestep ts)
	{
		// Render 2D
		Camera* mainCamera = nullptr;
		glm::mat4* cameraTransform = nullptr;
		{
			auto view = registry_.view<TransformComponent, CameraComponent>();
			for (auto entity : view)
			{
				auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

				if (camera.Primary)
				{
					mainCamera = &camera.Camera;
					cameraTransform = &transform.Transform;
					break;
				}
			}
        }
        if (mainCamera)
		{
			Renderer2D::BeginScene(mainCamera->GetProjection(), *cameraTransform);

			auto group = registry_.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

				Renderer2D::DrawQuad(transform, sprite.Color);
			}

			Renderer2D::EndScene();
		}
    }

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		viewport_width_ = width;
		viewport_height_ = height;

		// Resize our non-FixedAspectRatio cameras
		auto view = registry_.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if (!cameraComponent.FixedAspectRatio)
				cameraComponent.Camera.SetViewportSize(width, height);
		}

	}

}
