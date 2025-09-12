#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib>
#include <ctime>   
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
	void print(){
		std::cout <<"(" << "{" << src.first << "," << src.second << "}"  << "{" << dest.first << "," << dest.second << "}"<<")";

	}

};
int validneighbour(std::vector<std::vector<bool>>& isempty, int x, int y) {
	int ans;
	std::vector<int> valid;
	isempty[x][y] = false;
	if (x != 0 && isempty[x - 1][y] == true) valid.push_back(1);//up
	if ((y + 1) != isempty.size() && isempty[x][y + 1] == true) valid.push_back(2);//right
	if ((x + 1) != isempty.size() && isempty[x + 1][y] == true) valid.push_back(3);//down
	if (y != 0 && isempty[x][y - 1] == true) valid.push_back(4);//left
	if (valid.empty())return 0;
	else {
		int ranidx=rand()%valid.size();
		ans = valid[ranidx];
	}
	valid.clear();
	return ans;
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
	srand(time(0));
	int size = 4;
	std::vector<std::vector<std::vector<edge>>> graph(size, std::vector<std::vector<edge>>(size));
	std::vector<std::vector<bool>> isempty(size, std::vector<bool>(size, true));
	creat_maze(graph, isempty, 0, 0);
	for (int i = 0;i < size;i++) {
		std::cout << std::endl;
		for (int j = 0;j < size;j++) {
			std::cout << "       ";
			for (int k = 0;k < graph[i][j].size();k++) {
				graph[i][j][k].print();
				std::cout << " ";
			}
		}
	}
}
