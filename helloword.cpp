/*
本文件是对VScode的C++环境进行调试
time：2023-12-24
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int minStoneSum(vector<int>& piles, int k) {
        priority_queue<int> pq(piles.begin(), piles.end());
        for (int i = 0; i < k; i++) {
            int pile = pq.top();
            pq.pop();
            pile -= pile / 2;
            pq.push(pile);
        }
        int sum = 0;
        while (!pq.empty()) {
            sum += pq.top();
            pq.pop();
        }
        return sum;
    }
};

int main(){
    vector<int> piles={5,4,9};
    int k=2;
    Solution test;
    int sum=test.minStoneSum(piles,k);
    cout<<sum<<endl;
    return 0;

}