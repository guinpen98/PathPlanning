#include "node.h"

namespace pathPlanning {
	void Node::setStatus(NodeStatusE new_status) {
		node_status = new_status;
	}
	NodeStatusE Node::getStatus() const {
		return node_status;
	}
	void Node::setParentCoord(const int new_x, const int new_y) {
		parent_x = new_x;
		parent_y = new_y;
	}
	void Node::getParentCoord(int& p_x, int& p_y) {
		p_x = parent_x;
		p_y = parent_y;
	}
	void Node::setRCost(const int parent_r_cost) {
		r_cost = parent_r_cost + 1;
	}
	int Node::getRCost()const {
		return r_cost;
	}
	void Node::setHCost(const int dx, const int dy) {
		h_cost = ((dx > 0) ? dx : -dx) + ((dy > 0) ? dy : -dy);
	}
	int Node::getScore()const {
		return r_cost + h_cost;
	}

	void selectNode(const node_vector& node, int& select_node_x, int& select_node_y) {
		int min_cost = (std::numeric_limits<int>::max)();
		int min_score = (std::numeric_limits<int>::max)();
		for (int y = 0; y < node -> size(); y++) {
			for (int x = 0; x < (*node)[y].size(); x++) {
				//ステータスがOpen以外のノードを除外
				if ((*node)[y][x].getStatus() != OpenE) continue;
				int score = (*node)[y][x].getScore();
				int cost = (*node)[y][x].getRCost();
				//スコアが最小値未満と、最小値と同じで実コストが最小値以上のものを除外
				if (score > min_score) continue;
				if (score == min_score && cost >= min_cost) continue;
				//最小値の更新
				min_cost = cost;
				min_score = score;
				select_node_x = x;
				select_node_y = y;
			}
		}
	}
	void mobilizeOpenNode(const field_vector& field, node_vector& node, const int& select_node_x, const int& select_node_y) {
		int p_r_cost = (*node)[select_node_y][select_node_x].getRCost();
		if (select_node_x > 0)
			if ((*field)[select_node_y][select_node_x - 1] == 0) {
				if ((*node)[select_node_y][select_node_x - 1].getStatus() == NoneE) {
					(*node)[select_node_y][select_node_x - 1].setStatus(OpenE);
					(*node)[select_node_y][select_node_x - 1].setRCost(p_r_cost);
					(*node)[select_node_y][select_node_x - 1].setParentCoord(select_node_x, select_node_y);
				}
			}
		if (select_node_x < 127)
			if ((*field)[select_node_y][select_node_x + 1] == 0) {
				if ((*node)[select_node_y][select_node_x + 1].getStatus() == NoneE) {
					(*node)[select_node_y][select_node_x + 1].setStatus(OpenE);
					(*node)[select_node_y][select_node_x + 1].setRCost(p_r_cost);
					(*node)[select_node_y][select_node_x + 1].setParentCoord(select_node_x, select_node_y);
				}
			}
		if (select_node_y > 0)
			if ((*field)[select_node_y - 1][select_node_x] == 0) {
				if ((*node)[select_node_y - 1][select_node_x].getStatus() == NoneE) {
					(*node)[select_node_y - 1][select_node_x].setStatus(OpenE);
					(*node)[select_node_y - 1][select_node_x].setRCost(p_r_cost);
					(*node)[select_node_y - 1][select_node_x].setParentCoord(select_node_x, select_node_y);
				}
			}
		if (select_node_y < 71)
			if ((*field)[select_node_y + 1][select_node_x] == 0) {
				if ((*node)[select_node_y + 1][select_node_x].getStatus() == NoneE) {
					(*node)[select_node_y + 1][select_node_x].setStatus(OpenE);
					(*node)[select_node_y + 1][select_node_x].setRCost(p_r_cost);
					(*node)[select_node_y + 1][select_node_x].setParentCoord(select_node_x, select_node_y);
				}
			}
	}
}