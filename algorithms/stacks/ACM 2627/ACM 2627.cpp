#include <iostream>
using namespace std;
#include<queue>
#include<map>
#include<set>

typedef pair<int,int> coordinate;
typedef queue<coordinate> coordinateQueue;
typedef map<coordinate,bool> coordinateMap;

bool bordercheck(coordinate temp,int n){
    return (temp.first>=0&&temp.second>=0&&temp.first<n&& temp.second<n);
}

/*
this is revised by an AI, because I cannot find out problems in my code
Notes for BFS:
1. when doing the level order, use a variable to record the size of the queue
if not, then the size of the queue will be reassessed after each loop, instead of each level order
2. mark every point as visited immediately after visiting it
this prevents you from visiting the same points from different directions
*/

int BFS(coordinate start, coordinate end, int n, bool** maze) {
    int step = 0;
    queue<coordinate> searchlist = {};
    map<coordinate, bool> check;
    searchlist.push(start);
    check[start] = true;  // Mark start as visited immediately
    bool found = false;
    
    while(!searchlist.empty()) {
        int size = searchlist.size();
        
        for(int j = 0; j < size; j++) {
            auto temp = searchlist.front();
            searchlist.pop();
            
            if(temp == end) {
                found = true;
                break;
            }
            
            auto left = make_pair(temp.first - 1, temp.second);
            auto up = make_pair(temp.first, temp.second + 1);
            auto right = make_pair(temp.first + 1, temp.second);
            auto down = make_pair(temp.first, temp.second - 1);
            
            if(bordercheck(left, n) && !check[left] && !maze[left.first][left.second]) {
                check[left] = true;  // Mark as visited immediately when adding to queue
                searchlist.push(left);
            }
            if(bordercheck(right, n) && !check[right] && !maze[right.first][right.second]) {
                check[right] = true;  // Mark as visited immediately
                searchlist.push(right);
            }
            if(bordercheck(up, n) && !check[up] && !maze[up.first][up.second]) {
                check[up] = true;  // Mark as visited immediately
                searchlist.push(up);
            }
            if(bordercheck(down, n) && !check[down] && !maze[down.first][down.second]) {
                check[down] = true;  // Mark as visited immediately
                searchlist.push(down);
            }
        }
        
        if(found) break;  // If end is found, exit the while loop
        step++;
    }
    
    return found ? step : -1;
}
int main(){
    int n;
    cin>>n;
    bool** maze=new bool*[n];
    string temp;
    for (int i=0;i<n;i++){
        maze[i]=new bool[n];
        cin>>temp;
        for(int j=0;j<n;j++){
            maze[i][j]=bool(temp[j]-'0');
        }
    }
    
    int x1,y1,x2,y2;
    cin>>x1>>y1>>x2>>y2;
    coordinate start=make_pair(x1-1,y1-1);
    coordinate end=make_pair(x2-1,y2-1);
    int step=BFS(start,end,n,maze);
    cout<<step;

    return 0;
}
