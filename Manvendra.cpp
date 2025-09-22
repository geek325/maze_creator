#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<raylib.h>
#include <stack>
using namespace std;

class edge {
public:
	int row, col;
	edge(int r, int c) {
		row = r;
		col = c;
	}
};

class grid {
public:
	vector<vector<bool>>visited;
	vector<vector<vector<edge>>> g;
	pair<int,int>curr = { 0,0 };
	stack<pair<int, int>>btstack;
	int vertex;
	grid(int v){
		vertex = v;
		g.resize(v);
		for (int i = 0; i < v; i++) {
			g[i].resize(v);
		}
		visited.resize(vertex, vector<bool>(vertex, false));
		btstack.push({0,0});
		//make(); //for unanimated maze (pre built)
	}
	void display(){
		for (int i = 0; i < g.size();i++) {
			cout << "{";
			for (int j = 0; j < g[i].size();j++) {
				cout << "[";
				for (int k = 0; k < g[i][j].size();k++) {
					cout << "(" << g[i][j][k].row << "," << g[i][j][k].col << ")";
				}
				cout << "]";
			}
			cout << "}" << endl;
		}
	}

private:
	void make() {
		visited[0][0] = true;
		dfsr();
	}
	void addEdge(int r1, int c1, int r2, int c2) {
		g[r1][c1].push_back(edge(r2, c2));
		g[r2][c2].push_back(edge(r1, c1));
	}
	int check(int r, int c) {
		int count = 0;
		if (r != 0 && !visited[r - 1][c]) count++;
		if (r != vertex - 1 && !visited[r + 1][c]) count++;
		if (c != 0 && !visited[r][c - 1]) count++;
		if (c != vertex - 1 && !visited[r][c + 1]) count++;
		return count;
	}
	void join_rand(int r, int c) {
		vector<pair<int,int>>neighbour;
		if (r != 0 && !visited[r - 1][c])
			neighbour.push_back({ r - 1,c });
		if (r != vertex - 1 && !visited[r + 1][c])
			neighbour.push_back({ r + 1,c });
		if (c != 0 && !visited[r][c - 1])
			neighbour.push_back({ r,c - 1 });
		if (c != vertex - 1 && !visited[r][c + 1])
			neighbour.push_back({ r ,c + 1 });
		
		int rd = rand() % neighbour.size();
		int r2 = neighbour[rd].first;
		int c2 = neighbour[rd].second;
		addEdge(r,c,r2,c2);
		curr = {r2,c2};

	}
	void dfsr(int r=0, int c=0) {
		visited[r][c] = true;
		while (check(r, c)) {
			join_rand(r, c);
			for (int i = 0;i < g[r][c].size();i++) {
				int n = g[r][c][i].row;
				int m = g[r][c][i].col;
				if (visited[n][m]) continue;
				dfsr(n,m);
			}
		}
	}

public:
	void dfs() {
		visited[curr.first][curr.second] = true;
		if (check(curr.first, curr.second)) {
			btstack.push(curr);
			join_rand(curr.first, curr.second);
		}
		else {
			curr = btstack.top();
			btstack.pop();
		}

	}
};

int main() {
	int vertex = 50;
	srand(time(0));
	grid a(vertex);
	//a.display();
	

	int sw = 800;
	int sh = 800;
	int b = 3;

	float blockx = ((sw - b * (vertex+1)) / vertex);
	float blocky = ((sh - b * (vertex+1)) / vertex);

	float paddx = (sw - (blockx * vertex + b * (vertex + 1))) / 2;
	float paddy = (sh - (blocky * vertex + b * (vertex + 1))) / 2;


	InitWindow(sw, sh, "maze");
	SetTargetFPS(60);
	while (!WindowShouldClose()) {

		if(!a.btstack.empty()) a.dfs(); //for animated maze

		BeginDrawing();
		ClearBackground(BLACK);

		for (int i = 0; i < vertex; i++) {
			for (int j = 0; j < vertex; j++) {
				float x = b+j * (blockx+b) + paddx;
				float y = b+i * (blocky+b) + paddy;
				//DrawRectangle(x,y, blockx, blocky, WHITE);
				for (int k = 0; k < a.g[i][j].size(); k++){
					int nr = a.g[i][j][k].row;
					int nc = a.g[i][j][k].col;
					if (i == a.curr.first && j == a.curr.second) {
						DrawRectangle(x-b, y-b, blockx+b*2, blocky+b*2, RED);
					}
					else {
						if (nr == i && nc == j + 1) {
							DrawRectangle(x, y, blockx * 2 + b, blocky, WHITE);
						}
						if (nr == i + 1 && nc == j) {
							DrawRectangle(x, y, blockx, blocky * 2 + b, WHITE);
						}
					}
					
				}
			}
		}
		EndDrawing();
	}
	return 0;
}
