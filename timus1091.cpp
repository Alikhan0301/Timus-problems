#include "timus1091.hpp"
#include<iostream>

using namespace std;

int n, s;
int dp[55][55][55];
int gcd(int a, int b){
    if(b > a) swap(a, b);
    if(b == 0) return a;
    return gcd(b, a % b);
}

int main(){
    dp[0][0][0] = 1;
    for(int i = 0; i <= 50; ++i){
        for(int x = 0; x <= 50; ++x){
            for(int g = 0; g <= 50; ++g){
                for(int e = x + 1; e <= 50; ++e){
                    int newg = gcd(g, e);
                    dp[i + 1][e][newg] += dp[i][x][g];
                    if(dp[i + 1][e][newg] > 10000)
                        dp[i + 1][e][newg] = 10000;
                }
            }
        }
    }
    cin >> n >> s;
    int ans = 0;
    for(int g = 2; g <= 50; ++g){
        for(int mx = 1; mx <= s; ++mx){
            ans += dp[n][mx][g];
            if(ans > 10000)
                ans = 10000;
        }
    }
    cout << ans << "\n";
    return 0;
}
