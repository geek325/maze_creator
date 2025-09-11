#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>

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
	grid(int v) {
		vertex = v;
		g.resize(v);
		for (int i = 0; i < v; i++) {
			g[i].resize(v);
		}
		make();
	}
	void display() {
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
	void add(int r, int c, int row, int col) {
		g[r][c].push_back(edge(row, col));
	}
	void make() {
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
		int rd = rand() % check(v, r, c);
		if (r != 0 && !v[r - 1][c]) if (rd == 0) add(r, c, r - 1, c); else --rd;
		if (r != vertex - 1 && !v[r + 1][c]) if (rd == 0) add(r, c, r + 1, c); else --rd;
		if (c != 0 && !v[r][c - 1]) if (rd == 0) add(r, c, r, c - 1); else --rd;
		if (c != vertex - 1 && !v[r][c + 1]) if (rd == 0) add(r, c, r, c + 1); else --rd;

	}
	void dfsr(vector<vector<bool>>& v, int r, int c) {
		v[r][c] = true;
		while (check(v, r, c)) {
			join(v, r, c);
			for (int i = 0;i < g[r][c].size();i++) {
				if (v[g[r][c][i].row][g[r][c][i].col]) continue;
				dfsr(v, g[r][c][i].row, g[r][c][i].col);
			}
		}
	}
};


int main() {
	srand(time(0));
	grid a(4);
	a.display();
	return 0;
}