#include <stdio.h>
int main (){
    static int dp[21][21][21];
    for(int a = 0 ; a < 20 ; a++){
        for(int b = 0; b < 20 ; b++){
            for(int c = 0; c < 20; c++){
                if(a <= 0 && b <= 0 && c <= 0) dp[0][0][0] = 1;
                else if (a < b && b < c)
                    dp[a][b][c] = dp[a][b][c - 1] + dp[a][b - 1][c - 1] - dp[a][b - 1][c];
                else
                    dp[a][b][c] = dp[a - 1][b][c] + dp[a - 1][b - 1][c] + dp[a - 1][b][c - 1] - dp[a - 1][b - 1][c - 1]; 
            }
        }
    }
    int dig[][3];
    
}