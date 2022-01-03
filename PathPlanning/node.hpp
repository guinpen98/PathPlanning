#pragma once
#include <limits>
#include<array>
enum NodeStatusE {
	NoneE
	,OpenE
	,ClosedE
};

class Node {
private:
	NodeStatusE node_status = NoneE;
	int parent_x = 0;
	int parent_y = 0;
	int r_cost = 0;
	int h_cost = 0;
public:
	void setStatus(NodeStatusE new_status) {
		node_status = new_status;
	}
	NodeStatusE getStatus() const{
		return node_status;
	}
	void setParentCoord(const int new_x,const int new_y) {
		parent_x = new_x;
		parent_y = new_y;
	}
	void getParentCoord(int& p_x,int& p_y) {
		p_x = parent_x;
		p_y = parent_y;
	}
	void setRCost(const int parent_r_cost) {
		r_cost = parent_r_cost + 1;
	}
	int getRCost()const {
		return r_cost;
	}
	void setHCost(const int dx,const int dy) {
		h_cost = ((dx > 0) ? dx : -dx) + ((dy > 0) ? dy : -dy);
	}
	int getScore()const {
		return r_cost + h_cost;
	}
};

void selectNode(const std::array<std::array<Node, 128>, 72>& node,int& select_node_x,int& select_node_y) {
	int min_cost= (std::numeric_limits<int>::max)();
	int min_score= (std::numeric_limits<int>::max)();
	for (int y = 0; y < node.size(); y++) {
		for (int x = 0; x < node[y].size(); x++) {
			//ステータスがOpen以外のノードを除外
			if (node[y][x].getStatus() != OpenE) continue;
			int score = node[y][x].getScore();
			int cost = node[y][x].getRCost();
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
};
void mobilizeOpenNode(const std::array<std::array<int, 128>, 72>& field, std::array<std::array<Node, 128>, 72>& node, const int& select_node_x, const int& select_node_y) {
	int p_r_cost = node[select_node_y][select_node_x - 1].getRCost();
	if(select_node_x>0)
		if (field[select_node_y][select_node_x - 1] == 0) {
			node[select_node_y][select_node_x - 1].setStatus(OpenE);
			node[select_node_y][select_node_x - 1].setRCost(p_r_cost);
			node[select_node_y][select_node_x - 1].setParentCoord(select_node_x, select_node_y);
		}
	if (select_node_x < 1280)
		if (field[select_node_y][select_node_x + 1] == 0) {
			node[select_node_y][select_node_x + 1].setStatus(OpenE);
			node[select_node_y][select_node_x + 1].setRCost(p_r_cost);
			node[select_node_y][select_node_x + 1].setParentCoord(select_node_x, select_node_y);
		}
	if (select_node_y > 0)
		if (field[select_node_y - 1][select_node_x] == 0) {
			node[select_node_y - 1][select_node_x].setStatus(OpenE);
			node[select_node_y - 1][select_node_x].setRCost(p_r_cost);
			node[select_node_y - 1][select_node_x].setParentCoord(select_node_x, select_node_y);
		}
	if (select_node_y < 1280)
		if (field[select_node_y + 1][select_node_x] == 0) {
			node[select_node_y + 1][select_node_x].setStatus(OpenE);
			node[select_node_y + 1][select_node_x].setRCost(p_r_cost);
			node[select_node_y + 1][select_node_x].setParentCoord(select_node_x, select_node_y);
		}
};
