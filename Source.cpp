#include<iostream>
#include<vector>
#include <utility>
class edge {
public:
	std::pair<int, int> src;
	std::pair<int, int> dest;
	edge(int sx,int sy,int dx,int dy) {
		this->src.first = sx;
		this->src.second = sy;
		this->dest.first = dx;
		this->dest.second = dy;
	}

};
int validneighbour(std::vector<std::vector<bool>>& isempty, int startx, int starty) {

}
void creat_maze(std::vector<std::vector<std::vector<edge>>> &graph ,std::vector<std::vector<bool>> &isempty,int startx,int starty) {
	int size = graph.size();
	while (validneighbour(isempty, startx, starty)!=0) {
		switch (validneighbour(isempty, startx, starty)) {
		case 1://up
			graph[startx][starty].push_back(edge(startx, starty, startx - 1, starty));
			creat_maze(graph, isempty, startx - 1, starty);
			break;
		case 2://right
			graph[startx][starty].push_back(edge(startx, starty, startx, starty + 1));
			creat_maze(graph, isempty, startx, starty + 1);
			break;
		case 3://down
			graph[startx][starty].push_back(edge(startx, starty, startx + 1, starty));
			creat_maze(graph, isempty, startx + 1, starty);
			break;
		case 4://left
			graph[startx][starty].push_back(edge(startx, starty, startx, starty - 1));
			creat_maze(graph, isempty, startx, starty - 1);
			break;
		default://idk
			return;
		}
	}
}
void main() {
	int size = 4;
	std::vector<std::vector<std::vector<edge>>> graph(size, std::vector<std::vector<edge>>(size));
	std::vector<std::vector<bool>> isempty(size, std::vector<bool>(size, true));
}