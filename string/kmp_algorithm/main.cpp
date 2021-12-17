#include <iostream>
using namespace std;

void prefix_my(const char* str, int* next, int size) {

    int i = 0, j = 1;
    // [0, i] is the prefix_my area

    memset(next, 0, sizeof(int) * size);

    while (i < size && j < size - 1) {
        if (str[i] == str[j]) {
            next[j] = next[j - 1] + 1;
            i++;
        } else {
            i = next[i];
        }
        j++;
    }
}

void computePrefix_correct(const char* str, int* next, int size) {
    memset(next, 0, sizeof(int) * size);
    int j = 0;
    for (int i = 1; i < size; i++) {
        while (j > 0 && str[j] != str[i])
            j = next[j-1];

        if (str[j] == str[i])
            j++;
        next[i] = j;
    }
}

int KMPMatcher(const char* str1, const char* str2, int size1, int size2) {
    int* prefix = new int[size2];
//    computePrefix_correct(str2, prefix, size2);
    prefix_my(str2, prefix, size2);
    int j = 0;
    int i = 0;
    while (i < size1 && j < size2) {
        if (j == 0 || str1[i] == str2[j]) {
            i++; j++;
        } else {
            j = prefix[j];
        }
        cout << i << " " << j << "--";
    }

    if (j >= size2) {
        return i - size2;
    } else {
        return -1;
    }

}


int main() {

//    string str = "ababaaaba";
//    int* next = new int[str.size()];
//    for (int i = 0; i < str.size(); i++) {
//        cout << str[i] << " ";
//    }
//    prefix_my(str.data(), next, str.size());
//    cout << endl;
//    for (int i = 0; i < str.size(); i++) {
//        cout << next[i] << " ";
//    }
//    cout << endl;
//    computePrefix_correct(str.data(), next, str.size());
//    for (int i = 0; i < str.size(); i++) {
//        cout << next[i] << " ";
//    }

    string str1 = "abcaabbabcabaacbacba";
    string str2 = "abcabaa";
//    int* prefix = new int[str2.size()];
//    computePrefix_correct(str2.data(), prefix, str2.size());
//    for (int i = 0; i < str2.size(); i++) {
//        cout << prefix[i] << " ";
//    }

    cout << KMPMatcher(str1.data(), str2.data(), str1.size(), str2.size());


    return 0;
}
