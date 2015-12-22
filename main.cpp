#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <unistd.h>
#include <algorithm>
#include <ctime>
using namespace std;

class Step{
public:
  int counter;
  int x;
  int y;

  Step(int a, int b, int c){
    counter = a;
    x = b;
    y = c;
  }
};



bool comparisonFunction(Step a, Step b);

bool comparisonFunction(Step a, Step b){
  return (a.counter < b.counter);
}

int **board;
int s1,s2;
vector< vector<int> > chessBoard;
clock_t start;

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
    vector <int> checklist;
    for(int i = 0; i < s1; i++){
      for(int j = 0; j < s2; j++){
  	cout << chessBoard[i][j] << " ";
	// checklist.push_back(chessBoard[i][j]);
      }
      cout << endl;
    }
    // sort(checklist.begin(),checklist.end());
    // for(int i =0; i < checklist.size(); i++){
    //   cout << checklist[i]<< " ";
    // } 
    cout << "-------------------"<<endl;
    cout << "Time: " << (clock() - start)/ (double)(CLOCKS_PER_SEC / 1000) << " ms" << endl;
    exit(1);
  }
  //possible moves based on clock hand position
  Step one = Step(peek(x-2,y+1),x-2,y+1);
  Step two = Step(peek(x-1,y+2),x-1,y+2);
  Step four = Step(peek(x+1,y+2),x+1,y+2);
  Step five = Step(peek(x+2,y+1),x+2,y+1);
  Step seven = Step(peek(x+2,y-1),x+2,y-1);
  Step eight = Step(peek(x+1,y-2),x+1,y-2);
  Step ten = Step(peek(x-1,y-2),x-1,y-2);
  Step eleven = Step(peek(x-2,y-1),x-2,y-1);
  vector<Step> steps;
  steps.push_back(one);
  steps.push_back(two);
  steps.push_back(four);
  steps.push_back(five);
  steps.push_back(seven);
  steps.push_back(eight);
  steps.push_back(ten);
  steps.push_back(eleven);
  sort(steps.begin(),steps.end(),comparisonFunction);
  
  for(int i = 0; i < steps.size(); i++){
    if(steps[i].counter != 10){
      visitWithHeuristic(steps[i].x,steps[i].y,step);
    }
  }
  chessBoard[x][y] = 0;

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
  // Print out chessboard
  // for(int i = 0; i < m; i++){
  //   for(int j = 0; j < n; j++){
  //     cout << chessBoard[i][j] << " ";
  //   }
  //   cout << endl;
  // }
  visitWithHeuristic(0,0,1);
  cout << "No Tour Possible" << endl;

}


int main(int argc, char* argv[]){
    if(argc == 3){
        s1=atoi(argv[1]);
        s2=atoi(argv[2]);
	bruteForce();
        start = clock();
	warnsdorffsRule(s1,s2);
    }
    return 1;
}
