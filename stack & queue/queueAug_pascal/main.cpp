#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;
vector<vector<int>> resSetInt;

void getResult(int n) {
    queue<int> qData;
    bool begin = true;
    qData.push(0);
    qData.push(1);
    qData.push(0);

    for (int i = 0; i < n; i++) {
        vector<int> rowResInt;
        while (true) {
            int data1 = qData.front();
            if (data1 == 0 && !begin) {
                qData.push(0);
                begin = true;
                break;
            }
            qData.pop();
            begin = false;
            int data2 = qData.front();
            int resInt = data1 + data2;
            qData.push(resInt);
            rowResInt.push_back(resInt);
        }
        resSetInt.push_back(rowResInt);
    }
}

int getDigit(int n) {
    int i = 0;
    while (n > 0) {
        i++;
        n /= 10;
    }
    return i;
}

int getEachDigitLength(int depth) {
    int midIndex = resSetInt[depth].size() / 2;
    return getDigit(resSetInt[depth][midIndex]);
}

int main()
{
    int n;
    cin >> n;
    getResult(n);
    int numLength = getEachDigitLength(resSetInt.size() - 1);
    int lastNumCount = resSetInt[resSetInt.size() - 1].size();
    for (int i = 0; i < resSetInt.size() - 1; i++) {
        int space = lastNumCount - resSetInt[i].size();
        for (int j = 0; j <= space; j++) {
            cout << setw(numLength) << " ";
        }
        for (int j = 0; j < resSetInt[i].size(); j++) {
            cout << left << setw(numLength * 2) << resSetInt[i][j];
        }
        cout << endl;
    }
    return 0;
}
