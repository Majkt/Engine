#include "src/lib/scene/entity.h"

namespace majkt {

	Entity::Entity(entt::entity handle, Scene* scene)
		: entity_handle_(handle), scene_(scene)
	{
	}

} // namespace majkt
