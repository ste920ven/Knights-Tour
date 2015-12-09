#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <unistd.h>
using namespace std;


int **board;
int s1,s2;

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
    else wait(&cstat);
    
}

int main(int argc, char* argv[]){
    if(argc == 3){
        s1=atoi(argv[1]);
        s2=atoi(argv[2]);
        bruteForce();
    }
    return 1;
}
