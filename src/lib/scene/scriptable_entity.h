#ifndef MAJKT_SCENE_SCRIPTABLE_ENTITY_H_
#define MAJKT_SCENE_SCRIPTABLE_ENTITY_H_

#include "src/lib/scene/entity.h"

namespace majkt {

	class ScriptableEntity
	{
	public:
		virtual ~ScriptableEntity() {}
		template<typename T>
		T& GetComponent()
		{
			return entity_.GetComponent<T>();
		}
	protected:
		virtual void OnCreate() {}
		virtual void OnDestroy() {}
		virtual void OnUpdate(Timestep ts) {}
	private:
		Entity entity_;
		friend class Scene;
	};

} // namespace majkt

#endif  // MAJKT_SCENE_SCRIPTABLE_ENTITY_H_
