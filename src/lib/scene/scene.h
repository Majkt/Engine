#ifndef MAJKT_SCENE_SCENE_H_
#define MAJKT_SCENE_SCENE_H_

#include "src/lib/core/timestep.h"
#include "src/lib/core/uuid.h"
#include "src/lib/editor/editor_camera.h"

#include <memory>

#include <entt/entt.hpp>

class b2World;

namespace majkt {

	class Entity;

	// This defines a class called "Scene" which represents a scene in a game engine.
	// It has methods for creating and destroying entities within the scene, updating
	// the scene during runtime and in the editor, and getting the primary camera entity.
	class Scene
	{
	public:
		Scene();
		~Scene();

		static std::shared_ptr<Scene> Copy(std::shared_ptr<Scene> other);

		Entity CreateEntity(const std::string& name = std::string());
		Entity CreateEntityWithUUID(Uuid uuid, const std::string& name = std::string());
		void DestroyEntity(Entity entity);

		void OnRuntimeStart();
		void OnRuntimeStop();
		void OnUpdateRuntime(Timestep ts);
		void OnUpdateEditor(Timestep ts, EditorCamera& camera);
		void OnViewportResize(uint32_t width, uint32_t height);
		void DuplicateEntity(Entity entity);
		
		Entity GetPrimaryCameraEntity();
	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);

		entt::registry registry_;
		uint32_t viewport_width_{0}, viewport_height_{0};

		b2World* physics_world_ = nullptr;
        friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;
	};

} // namespace majkt

#endif  // MAJKT_SCENE_SCENE_H_
