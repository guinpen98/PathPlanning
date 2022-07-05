#ifndef PATH_PLANNING_CONFIGURATION_H
#define PATH_PLANNING_CONFIGURATION_H
#include<array>
#include<memory>

namespace path_planning {
	constexpr int width = 128;
	constexpr int height = 72;


	using field_type = int;
	using field_array = std::unique_ptr<field_type[]>;
}

#endif // !PATH_PLANNING_CONFIGURATION_H