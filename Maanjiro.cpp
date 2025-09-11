#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<raylib.h>
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
	vector<vector<vector<edge>>> g;
	int vertex;
	grid(int v){
		vertex = v;
		g.resize(v);
		for (int i = 0; i < v; i++) {
			g[i].resize(v);
		}
		make();
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
	void add(int r1, int c1, int r2, int c2) {
		g[r1][c1].push_back(edge(r2, c2));
		g[r2][c2].push_back(edge(r1, c1));
	}
	void make(){
		vector<vector<bool>>visited(vertex, vector<bool>(vertex, false));
		visited[0][0] = true;
		dfsr(visited, 0, 0);
	}
	int check(vector<vector<bool>>& v, int r, int c) {
		int count = 0;
		if (r != 0 && !v[r - 1][c]) count++;
		if (r != vertex - 1 && !v[r + 1][c]) count++;
		if (c != 0 && !v[r][c - 1]) count++;
		if (c != vertex - 1 && !v[r][c + 1]) count++;
		return count;
	}
	void join(vector<vector<bool>>& v, int r, int c) {
		int count = 0;
		vector<pair<int,int>>neighbour;
		if (r != 0 && !v[r - 1][c]){
			neighbour.push_back({ r - 1,c });
			count++;
		}
		if (r != vertex - 1 && !v[r + 1][c]){
			neighbour.push_back({ r + 1,c });
			count++;
		}
		if (c != 0 && !v[r][c - 1]){
			neighbour.push_back({ r,c - 1 });
			count++;
		}
		if (c != vertex - 1 && !v[r][c + 1]){
			neighbour.push_back({ r ,c + 1 });
			count++;
		}
		int rd = rand() % count;
		int r2 = neighbour[rd].first;
		int c2 = neighbour[rd].second;
		add(r,c,r2,c2);

	}
	void dfsr(vector<vector<bool>>& v, int r, int c) {
		while (check(v, r, c)) {
			join(v, r, c);
			for (int i = 0;i < g[r][c].size();i++) {
				int n = g[r][c][i].row;
				int m = g[r][c][i].col;
				if (v[n][m]) continue;
				v[n][m] = true;
				dfsr(v, n,m);
			}
		}
	}
};

int main() {
	int vertex = 50;
	srand(time(0));
	grid a(vertex);
	a.display();
	

	int sw = 800;
	int sh = 800;
	int b = 2;

	float blockx = (sw - b * 2) / vertex;
    float blocky = (sh - b * 2) / vertex;
	InitWindow(sw, sh, "maze");
	while (!WindowShouldClose()) {

		BeginDrawing();
		ClearBackground(WHITE);
		DrawRectangle(0, 0, sw, sh, BLACK);

		for (int i = 0; i < vertex; i++) {
			for (int j = 0; j < vertex; j++) {
				float x = b + j * (blockx + b);
				float y = b + i * (blocky + b);
				DrawRectangle(x,y, blockx, blocky, WHITE);
				for (int k = 0; k < a.g[i][j].size(); k++) {
					int ni = a.g[i][j][k].row;
					int nj = a.g[i][j][k].col;

					if (ni == i && nj == j + 1) {
						DrawRectangle(x + blockx, y, b, blocky, WHITE);
					}
					if (ni == i + 1 && nj == j) {
						DrawRectangle(x, y + blocky, blockx, b, WHITE);
					}
				}
			}
		}
		EndDrawing();
	}
	return 0;
}