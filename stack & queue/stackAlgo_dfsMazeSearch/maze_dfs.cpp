class Result {
public:
    int x;
    int y;
};

vector<Result> result;

void maze(int map[][10], int x, int y) {
    if (map[x][y] == 1)
        return;

    if (map[x][y] == 2) {
        for (int i = 0; i < result.size(); i++) {
            cout << " (" << result[i].x << " " << result[i].y << ") ";
        }
    }

    map[x][y] = 1;
    Result res; res.x = x; res.y = y;
    result.push_back(res);

    maze(map, x, y + 1);

    maze(map, x + 1, y);

    maze(map, x, y - 1);

    maze(map, x - 1, y);

    result.pop_back();
    map[x][y] = 0;
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

    maze(map, 1, 1);

    return 0;
}