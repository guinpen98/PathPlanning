#ifndef PATH_PLANNING_CONFIGURATION_H
#define PATH_PLANNING_CONFIGURATION_H
#include<array>
#include<memory>

namespace pathPlanning {
	constexpr int width = 128;
	constexpr int height = 72;


	using field_type = int;
	using field_array = std::array<field_type, width>;
	using field_vector = std::unique_ptr<std::array<field_array, height>>;
}

#endif // !PATH_PLANNING_CONFIGURATION_H