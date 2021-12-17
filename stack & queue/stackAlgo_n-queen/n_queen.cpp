#include <iostream>
#include <vector>
using namespace std;

class Result {
public:
    int x;
    int y;
};

bool check(int map[][8], int x, int y, int size, vector<Result> result) {
    for (int i = 0; i < result.size(); i++) {
        if (result[i].x + result[i].y == x + y
                || result[i].x - result[i].y == x - y
                || result[i].x == x || result[i].y == y)
            return false;
    }
    return true;
}

void show(int map[][8], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (map[i][j] == 0)
                cout << "- ";
            else
                cout << "* ";
        }
        cout << endl;
    }
    cout << "--------------------" << endl;
}

void putQueen(int map[][8], int x, int y, int size, vector<Result> result) {
    if (x < 0 || x >= size || y < 0 || y >= size|| !check(map, x, y, size, result)) {
        return;
    }

    map[x][y] = 1;
    Result res; res.x = x; res.y = y;
    result.push_back(res);

    if (y == size - 1) {
        show(map, size);
        map[x][y] = 0;
        return;
    }

    for (int i = 0; i < size; i++) {
        putQueen(map, i, y + 1, size, result);
    }

    map[x][y] = 0;
}

int main() {
    int map[8][8];
    memset(map, 0, sizeof(map));
    vector<Result> res;

    for (int i = 0; i < 8; i++) {
        putQueen(map, i, 0, 8, res);
    }
    return 0;
}
