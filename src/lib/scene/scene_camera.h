#ifndef MAJKT_SCENE_SCENECAMERA_H_
#define MAJKT_SCENE_SCENECAMERA_H_

#include "src/lib/renderer/camera.h"

namespace majkt {

	class SceneCamera : public Camera
	{
	public:
		SceneCamera();
		virtual ~SceneCamera() = default;

		void SetOrthographic(float size, float nearClip, float farClip);

		void SetViewportSize(uint32_t width, uint32_t height);

		float GetOrthographicSize() const { return orthographic_size_; }
		void SetOrthographicSize(float size) { orthographic_size_ = size; RecalculateProjection(); }
	private:
		void RecalculateProjection();
	private:
		float orthographic_size_ = 10.0f;
		float orthographic_near_ = -1.0f, orthographic_far_ = 1.0f;

		float aspect_ratio_ = 0.0f;
	};

} // namespace majkt

#endif  // MAJKT_SCENE_SCENECAMERA_H_
