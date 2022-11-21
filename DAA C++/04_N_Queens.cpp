#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> result;
        vector<string> temp(n, string(n, '.'));
        int dp[n];  //put column index for each row where queen is placed
        
        backtrack(result, temp, dp, 0, n);
        return result;
    }
    
    void backtrack(vector<vector<string>>& result, 
                   vector<string>& temp, int dp[], int row, int n){
        if(row == n) {
            result.push_back(temp);
            return;
        }
        for(int col=0; col<n; col++){
            if(valid(dp, row, col, n)){
                dp[row] = col;
                temp[row][col] = 'Q';
                backtrack(result, temp, dp, row+1, n);
                temp[row][col] = '.';
            }
        }
    }
    
    bool valid(int dp[], int row, int col, int n){
        for(int i=0; i<row; i++){
            if(dp[i] == col || abs(row-i)==abs(dp[i]-col)) {
                return false;
            }
        }
        return true;
    }
};

int main()
{
    Solution obj;
    vector<vector<string>> ans = obj.solveNQueens(4);
    for(auto s : ans[0]){
        cout << s << "\n";
    }
    
    return 0;
}