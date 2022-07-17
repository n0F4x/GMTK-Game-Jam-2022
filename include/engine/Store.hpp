#pragma once

#include <map>
#include <string>


namespace engine {

	/**
	 * @brief	Stores are useful to share data between State(s) via StateMachines
	*/
	class Store {
	public:
		std::string* add(const std::string& id, const std::string& item);
		/**
		 * @brief	Access an item of the store
		 * @param id 
		 * @return	!!! nullptr if there is no item with such id !!!
		*/
		std::string* get(const std::string_view& id);

	private:
		std::map<const std::string, std::string, std::less<>> _data;
	};

}