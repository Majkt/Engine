#ifndef MAJKT_SCENE_SCENE_SERIALIZER_H_
#define MAJKT_SCENE_SCENE_SERIALIZER_H_

#include "src/lib/scene/scene.h"

namespace majkt {

	class SceneSerializer
	{
	public:
		SceneSerializer(const std::shared_ptr<Scene>& scene);

		void Serialize(const std::string& filepath);
		bool Deserialize(const std::string& filepath);
	private:
		std::shared_ptr<Scene> scene_;
	};

} // namespace majkt

#endif  // MAJKT_SCENE_SCENE_SERIALIZER_H_
