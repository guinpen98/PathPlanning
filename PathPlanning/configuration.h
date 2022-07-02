#ifndef PATH_PLANNING_CONFIGURATION_H
#define PATH_PLANNING_CONFIGURATION_H
#include<array>
#include<memory>

namespace pathPlanning {
	using field_type = int;
	using field_array = std::array<field_type, 128>;
	using field_vector = std::unique_ptr<std::array<field_array, 72>>;

}

#endif // !PATH_PLANNING_CONFIGURATION_H