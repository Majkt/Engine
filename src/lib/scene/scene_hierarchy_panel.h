#ifndef MAJKT_SCENE_SCENE_HIERARCHY_PANEL_H_
#define MAJKT_SCENE_SCENE_HIERARCHY_PANEL_H_

#include "src/lib/core/timestep.h"
#include "src/lib/scene/scene.h"
#include "src/lib/scene/entity.h"

#include <memory>

#include <entt/entt.hpp>

namespace majkt {

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const std::shared_ptr<Scene>& scene);

		void SetContext(const std::shared_ptr<Scene>& scene);

		void OnImGuiRender();
	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);

		std::shared_ptr<Scene> context_;
		Entity selection_context_;
	};

} // namespace majkt

#endif  // MAJKT_SCENE_SCENE_HIERARCHY_PANEL_H_
