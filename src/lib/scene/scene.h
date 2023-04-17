#ifndef MAJKT_SCENE_SCENE_H_
#define MAJKT_SCENE_SCENE_H_

#include "src/lib/core/timestep.h"
#include <memory>

#include <entt/entt.hpp>

namespace majkt {

	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());

		void OnUpdate(Timestep ts);
        void OnViewportResize(uint32_t width, uint32_t height);
	private:
		entt::registry registry_;
		uint32_t viewport_width_{0}, viewport_height_{0};

        friend class Entity;
	};

} // namespace majkt

#endif  // MAJKT_SCENE_SCENE_H_
