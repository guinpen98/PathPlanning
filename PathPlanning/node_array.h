#ifndef PATH_PLANNING_NODE_ARRAY_H
#define PATH_PLANNING_NODE_ARRAY_H
#include"node.h"

namespace path_planning {

	template <int X, int Y>
	class Nodes {
		using nodeVector = std::array<Node, X>;
		using nodeArray = std::unique_ptr<std::array<nodeVector, Y>>;

		nodeArray nodes = std::make_unique<std::array<nodeVector, Y>>;
	};

	/*using nodeArray = std::array<node_array, 72>();
	node_array makeNodeArray(const int x, const int y) {
		node_array nodes = std::make_unique<Node[]>(width * height);
		return nodes;
	}*/
}
#endif // !PATH_PLANNING_NODE_ARRAY_H