#include "engine/Store.hpp"

#include <iostream>

using namespace engine;


std::string* Store::add(const std::string& id, const std::string& item) {
	if (auto [it, result] = _data.try_emplace(id, item); !result) {
		std::cerr << "\nStore: Failed adding item \"" << id << "\", as one with the same is already added.\n";
	}
	else {
		return &it->second;
	}
	return nullptr;
}

std::string* Store::get(const std::string_view& id) {
	if (auto it = _data.find(id); it != _data.end()) {
		return &it->second;
	}
	std::cerr << "\nStore: Failed finding the following item: \"" << id << "\"\n";
	return nullptr;
}
