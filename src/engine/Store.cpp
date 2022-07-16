#include "engine/Store.hpp"

#include <iostream>

using namespace engine;


void Store::add(const std::string& id, const std::string& item) {
	if (!_data.try_emplace(id, item).second) {
		std::cerr << "\nStore: Failed adding item \"" << id << "\", as one with the same is already added.\n";
	}
}

std::string* Store::get(const std::string_view& id) {
	if (auto it = _data.find(id); it != _data.end()) {
		return &it->second;
	}
	std::cerr << "\nStore: Failed finding the following item: \"" << id << "\"\n";
	return nullptr;
}
