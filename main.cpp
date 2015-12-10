#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <unistd.h>
#include <algorithm>
using namespace std;


int **board;
int s1,s2;
vector< vector<int> > chessBoard;


void visit(int x,int y,int step){
    board[x][y]=step;
    step++;
    if(step>s1*s2) {
        for(int i=0;i<s1;i++){
            for (int j=0;j<s2; j++) {
                cout<<board[i][j]<<" ";
            }
            cout<<endl;
        }
        exit(1);
    }

    if(x+2<s1 && y+1<s2 && board[x+2][y+1]==0){
        visit(x+2,y+1,step);
    }if(x+2<s1 && y-1>=0 && board[x+2][y-1]==0){
        visit(x+2,y-1,step);
    }if(x-2>=0 && y+1<s2 && board[x-2][y+1]==0){
        visit(x-2,y+1,step);
    }if(x-2>=0 && y-1>=0 && board[x-2][y-1]==0){
        visit(x-2,y-1,step);
    }if(y+2<s2 && x+1<s1 && board[x+1][y+2]==0){
        visit(x+1,y+2,step);
    }if(y+2<s2 && x-1>=0 && board[x-1][y+2]==0){
        visit(x-1,y+2,step);
    }if(y-2>=0 && x+1<s1 && board[x+1][y-2]==0){
       visit(x+1,y-2,step);
    }if(y-2>=0 && x-1>=0 && board[x-1][y-2]==0){
       visit(x-1,y-2,step);
    }
    board[x][y]=0;
}

int peek(int x, int y){
  if(x < 0 || y < 0 || x >= s1 || y >= s2 || chessBoard[x][y] != 0){
    return 10;
  }
  int counter = 0;
  if((x-2 >= 0) && (x-2 < s1) &&( y+1 >=0 )&&( y+1 < s2)){
    if(chessBoard[x-2][y+1] == 0){
      counter++;
    }
  }
  if((x-1 >= 0) && (x-1 < s1) && (y+2 >=0) && (y+2 < s2)){
  if(chessBoard[x-1][y+2] == 0){
    counter++;
  }
 }
  if((x+1 >= 0) && (x+1 < s1) && (y+2 >=0) && (y+2 < s2)){
    if(chessBoard[x+1][y+2] == 0){
    counter++;
    }
  }
  if((x+2 >= 0) && (x+2 < s1) && (y+1 >=0) && (y+1 < s2)){
    if(chessBoard[x+2][y+1] == 0){
    counter++;
    }
  }
  if((x+2 >= 0) && (x+2 < s1) && (y-1 >=0) && (y-1 < s2)){
    if(chessBoard[x+2][y-1] == 0){
    counter++;
    }
  }
  if((x+1 >= 0) && (x+1 < s1) && (y-2 >=0) &&( y-2 < s2)){
    if(chessBoard[x+1][y-2] == 0){
    counter++;
    }
  }
  if((x-1 >= 0) && (x-1 < s1) &&( y-2 >=0) &&( y-2 < s2)){
    if(chessBoard[x-1][y-2] == 0){
    counter++;
    }
  }
  if((x-2 >= 0) &&( x-2 < s1) && (y-1 >=0) && (y-1 < s2)){
    if(chessBoard[x-2][y-1] == 0){
      counter++;
    }
  }
  
  return counter;
}


void visitWithHeuristic(int x, int y, int step){
  chessBoard[x][y] = step;
  step++;
  //If all spaces reached
  if(step > s1 * s2){
    for(int i = 0; i < s1; i++){
      for(int j = 0; j < s2; j++){
	cout << chessBoard[i][j] << " ";
      }
      cout << endl;
    }
    exit(1);
  }
  int min = 10;
  int nextX = x;
  int nextY = y;
  //possible moves based on clock hand position
  int one = peek(x-2,y+1);
  if(one < min){
    min = one;
    nextX = x-2;
    nextY = y+1;
  }
  int two = peek(x-1,y+2);
  if(two < min){
    min = two;
    nextX = x-1;
    nextY = y+2;
  }
  int four = peek(x+1,y+2);
  if(four < min){
    min = four;
    nextX = x+1;
    nextY = y+2;
  }
  int five = peek(x+2,y+1);
  if(five < min){
    min = five;
    nextX = x+2;
    nextY = y+1;
  }
  int seven = peek(x+2,y-1);
  if(seven < min){
    min = seven;
    nextX = x+2;
    nextY = y-1;
  }
  int eight = peek(x+1,y-2);
  if(eight < min){
    min = eight;
    nextX = x+1;
    nextY = y-2;
  }
  int ten = peek(x-1,y-2);
  if(ten < min){
    min = ten;
    nextX = x-1;
    nextY = y-2;
  }
  int eleven = peek(x-2,y-1);
  if(eleven < min){
    min = eleven;
    nextX = x-2;
    nextY = y-1;
  }
 
  visitWithHeuristic(nextX,nextY,step);
}


void bruteForce(){
    int step=1;
    board=new int*[s1];
    for (int i=0; i<s1; ++i) {
        board[i]=new int[s2];
        for (int j=0; j<s2; ++j) {
            board[i][j]=0;
        }
    }
    pid_t pid = fork();
    int cstat=-1;
    if (pid == 0) visit(0,0,1);
    else wait(cstat);
    
}


void warnsdorffsRule(int m, int n){
  //intialize chessboard
  for(int i = 0; i < m; i++){
    vector<int> temp;
    for(int j = 0; j < n; j++){
      temp.push_back(0);
    }
    chessBoard.push_back(temp);
  }
  //Print out chessboard
  // for(int i = 0; i < m; i++){
  //   for(int j = 0; j < n; j++){
  //     cout << chessBoard[i][j] << " ";
  //   }
  //   cout << endl;
  // }
  visitWithHeuristic(0,0,1);
  

}


int main(int argc, char* argv[]){
    if(argc == 3){
        s1=atoi(argv[1]);
        s2=atoi(argv[2]);
        //bruteForce();
	warnsdorffsRule(s1,s2);
    }
    return 1;
}
