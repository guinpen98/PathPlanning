#ifndef PATH_PLANNING_NODE_H
#define PATH_PLANNING_NODE_H
#include <limits>
#include<array>
#include<memory>
#include"configuration.h"

namespace path_planning {
	enum NodeStatusE {
		NoneE
		, OpenE
		, ClosedE
	};

	class Node {
	private:
		NodeStatusE node_status = NoneE;
		int parent_x = 0;
		int parent_y = 0;
		int r_cost = 0;
		int h_cost = 0;
	public:
		void setStatus(NodeStatusE new_status);
		NodeStatusE getStatus()const;
		void setParentCoord(const int new_x, const int new_y);
		void getParentCoord(int& p_x, int& p_y);
		void setRCost(const int parent_r_cost);
		int getRCost()const;
		void setHCost(const int dx, const int dy);
		int getScore()const;
	};

	using node_array = std::unique_ptr<Node[]>;

	void selectNode(const node_array& node, int& select_node_x, int& select_node_y);
	void mobilizeOpenNode(const field_array& field, node_array& node, const int& select_node_x, const int& select_node_y);
}
#endif // !PATH_PLANNING_NODE_H