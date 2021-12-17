#include <iostream>
#include <stack>
#include <vector>
using namespace std;

void stackPermutation(vector<int> inSeq, vector<int> outSeq, stack<int> st, int depth) {
    if (depth == inSeq.size()) {
        for (int i : outSeq) {
            cout << i << " ";
        }
        while (!st.empty()) {
            int val = st.top();
            st.pop();
            cout << val << " ";
        }
        cout << endl;
        return;
    }

    if (!st.empty()) {
        int value = st.top();
        st.pop();
        outSeq.push_back(value);
        stackPermutation(inSeq, outSeq, st, depth);
        st.push(value);
        outSeq.pop_back();
    }

    int value = inSeq[depth];
    st.push(value);
    stackPermutation(inSeq, outSeq, st, depth + 1);

}

int main() {
    stack<int> st;
    vector<int> inSeq;
    vector<int> outSeq;
    inSeq.push_back(1);
    inSeq.push_back(2);
    inSeq.push_back(3);
    stackPermutation(inSeq, outSeq, st, 0);
}