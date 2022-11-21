#include <bits/stdc++.h>
using namespace std;

bool valid(int dp[], int row, int col, int n){
    for(int i=0; i<row; i++){
        if(dp[i] == col || abs(row-i)==abs(dp[i]-col))
            return false;
    }
    return true;
}

void backtrack(vector<vector<string>>& ans, vector<string>& board, int dp[], int row, int n){
    if(row == n){
        ans.push_back(board);
        return;
    }
    for(int col=0; col<n; col++){
        if(valid(dp, row, col, n)){
            dp[row] = col;
            board[row][col] = 'Q';
            backtrack(ans, board, dp, row+1, n);
            board[row][col] = '.';
        }
    }
}

vector<string> solveNQueen(int n){
    vector<vector<string>> ans;
    vector<string> board(n, string(n,'.'));
    int dp[n]; // put column index for each row where queen is placed
    backtrack(ans, board, dp, 0, n);
    return ans[0];
}

int main()
{
    vector<string> ans = solveNQueen(4);
    for(auto s : ans){
        cout << s << '\n';
    }
    return 0;
}