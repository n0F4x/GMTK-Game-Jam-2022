#include "engine/components/Animator.hpp"

using namespace engine;


Animation* Animator::addAnimation(const std::string& name, std::unique_ptr<Animation> animation) {
	animation->_object = object();
	if (auto [it, success] = _animations.try_emplace(name, std::move(animation)); success) {
		return it->second.get();
	}
	return nullptr;
}

Animation* Animator::findAnimation(const std::string_view& name) {
	if (auto it = _animations.find(name); it != _animations.end()) {
		return it->second.get();
	}
	return nullptr;
}

void Animator::deleteAnimation(const std::string& name) {
	_animations.erase(name);
}

void Animator::animate(sf::Time deltaTime) const {
	for (auto const& [name, animation] : _animations) {
		if (animation->isActive()) {
			animation->update(deltaTime);
		}
	}
}
