#include <iostream>
using namespace std;

int knapsack(int n, int s[], int v[], int C) {
  // Please fill the code
  int solution[1000][150];
  solution[0][0]=0;
  for (int i=0;i<=n;i++){
      for (int j=0;j<=C;j++){
          if (i==0||j==0) solution[i][j]=0;
          else if(i>0 && s[i-1]>j) solution[i][j]=solution[i-1][j];
          else solution[i][j] =max(solution[i-1][j],solution[i-1][j-s[i-1]]+v[i-1]);
      }
  }
  return solution[n][C];
}

int main() 
{
  int n, C,s[2000], v[2000];
  cin >> C >> n;
  
  for (int i = 0; i < n; i++)
    cin >> s[i] >> v[i];
  
  cout << knapsack(n, s, v, C) << endl;
  return 0;
}
