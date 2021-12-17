#include <iostream>
#include <queue>
using namespace std;

class ResultNode {
public:
    int x, y, prev;
    ResultNode(int x, int y, int prev) {
        this->x = x;
        this->y = y;
        this->prev = prev;
    }
};

vector<ResultNode> resSet;

void findPath(int map[][10], int m, int n) {
    ResultNode start(1, 1, -1);
    queue<ResultNode> path;
    path.push(start);

    while (!path.empty()) {
        ResultNode current = path.front();
        resSet.push_back(current);

        int currentIndex = resSet.size() - 1;
        path.pop();
        if (map[current.x][current.y] == 2) break;

        if (current.x + 1 < m && map[current.x + 1][current.y] != 1) {
            map[current.x + 1][current.y] = 1;
            ResultNode newNode(current.x + 1, current.y, currentIndex);
            path.push(newNode);
            resSet.push_back(newNode);
        }

        if (current.x - 1 >= 0 && map[current.x - 1][current.y] != 1) {
            map[current.x - 1][current.y] = 1;
            ResultNode newNode(current.x - 1, current.y, currentIndex);
            path.push(newNode);
            resSet.push_back(newNode);
        }

        if (current.y + 1 < n && map[current.x][current.y + 1] != 1) {
            map[current.x][current.y - 1] = 1;
            ResultNode newNode(current.x, current.y + 1, currentIndex);
            path.push(newNode);
            resSet.push_back(newNode);
        }

        if (current.y - 1 >= 0 && map[current.x][current.y - 1] != 1) {
            map[current.x][current.y - 1] = 1;
            ResultNode newNode(current.x, current.y - 1, currentIndex);
            path.push(newNode);
            resSet.push_back(newNode);
        }
    }
}

void display(int depth) {
    ResultNode current = resSet[depth];
    if (current.prev == -1) {
        cout << "(" << current.x << ", " << current.y << ")";
        return;
    }
    display(current.prev);
    cout << "(" << current.x << ", " << current.y << ")";

}

int main() {
    int map[][10] = {
            {1,1,1,1,1,1,1,1,1,1},
            {1,0,0,1,0,0,0,1,0,1},
            {1,0,0,1,0,0,0,1,0,1},
            {1,0,0,0,0,1,1,0,0,1},
            {1,0,1,1,1,0,0,0,0,1},
            {1,0,0,0,1,0,0,0,0,1},
            {1,0,1,0,0,0,1,0,0,1},
            {1,0,1,1,1,0,1,1,0,1},
            {1,1,0,0,0,0,0,0,2,1},
            {1,1,1,1,1,1,1,1,1,1}
    };
    findPath(map, 10, 10);
    display(resSet.size() - 1);
    return 0;
}
