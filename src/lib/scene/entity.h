#ifndef MAJKT_SCENE_ENTITY_H_
#define MAJKT_SCENE_ENTITY_H_

#include "src/lib/scene/scene.h"
#include "src/lib/scene/components.h"
#include "src/lib/core/uuid.h"
#include <memory>

#include <entt/entt.hpp>

#include <glog/logging.h>
#include "glog/stl_logging.h"
#include <iostream>

namespace majkt {

	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
            if (HasComponent<T>()) LOG(WARNING) << "Entity already has component!";
			T& component = scene_->registry_.emplace<T>(entity_handle_, std::forward<Args>(args)...);
			scene_->OnComponentAdded<T>(*this, component);
			return component;		
			
		}

		template<typename T, typename... Args>
		T& AddOrReplaceComponent(Args&&... args)
		{
			T& component = scene_->registry_.emplace_or_replace<T>(entity_handle_, std::forward<Args>(args)...);
			scene_->OnComponentAdded<T>(*this, component);
			return component;
		}

		template<typename T>
		T& GetComponent()
		{
            if (!HasComponent<T>()) LOG(WARNING) << "Entity does not have component!";
			return scene_->registry_.get<T>(entity_handle_);
		}

		template<typename T>
		bool HasComponent()
		{
			return scene_->registry_.all_of<T>( entity_handle_ );
		}

		template<typename T>
		void RemoveComponent()
		{
            if (!HasComponent<T>()) LOG(WARNING) << "Entity does not have component!";
			scene_->registry_.remove<T>(entity_handle_);
		}

		Uuid GetUUID() { return GetComponent<IDComponent>().ID; }
		const std::string& GetName() { return GetComponent<TagComponent>().Tag; }
		
		operator bool() const { return entity_handle_ != entt::null; }
		operator entt::entity() const { return entity_handle_; }
		operator uint32_t() const { return (uint32_t)entity_handle_; }

		bool operator==(const Entity& other) const
		{
			return entity_handle_ == other.entity_handle_ && scene_ == other.scene_;
		}

		bool operator!=(const Entity& other) const
		{
			return !(*this == other);
		}
		private:
		entt::entity entity_handle_{entt::null};
		Scene* scene_ = nullptr;
	};
    
} // namespace majkt

#endif  // MAJKT_SCENE_ENTITY_H_
