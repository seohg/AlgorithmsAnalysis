#include <iostream>
#include <cstdlib>
#include <limits>
#include <vector>

#define MAX_LEN 128
using namespace std;

void load_problem(vector<int> *p,int t); //load 10 problem
void generate_problem(vector<int> *p); //make random problem (optional function)
void mcm(vector<int> *p,int n, int (*arr)[MAX_LEN],int (*small)[MAX_LEN]); //mcm algorithm
void print_optimal(int (*small)[MAX_LEN],int i,int j); //print optimal solution

int main(){
    vector<int> p; 
    int arr[MAX_LEN][MAX_LEN];  
    int small[MAX_LEN][MAX_LEN]; 
    int n;
    
    for(int t = 0;t<10;t++){
        printf("Test : %d\n\n",t+1); //문제 번호 출력
        //generate_problem(&p); //optional function
        load_problem(&p,t); //해당 문제 vector에 저장

        for(int s=0;s<p.size()-2;s++){ //문제 행렬 출력
            if(p.at(s+2)!=0){
                printf("A[%d] : %dX%d ",s+1,p.at(s+1),p.at(s+2));
            }
        }

        printf("\n\n");
        n = p.size()-2; 

        mcm(&p,n,arr,small); //mcm algorithm
        print_optimal(small, 1, n); //optimal solution 출력
        printf("\nvalue : %d" ,arr[1][int(p.size()-2)]);

        p.clear(); //vector 초기화
        printf("\n\n");
    }
    
}

void generate_problem(vector<int> *p){ 
    /* optional function just for my study */
    int len = rand()%10+20;
    printf("len: %d\n",len);
    p->push_back(0);
    for(int i=1;i<=len;i++){
        p->push_back(rand()%50);
        printf("p %d\n",p->at(i));
    }
}

void load_problem(vector<int> *p,int t){
    int problem[10][10] = {
            {20,10,50,5,30,0,0,0,0,0},
            {10,5,40,10,0,0,0,0,0,0},
            {20,30,40,10,20,0,0,0,0,0},
            {15,5,20,10,0,0,0,0,0,0},
            {5,10,15,10,5,5,0,0,0,0},
            {10,10,20,15,0,0,0,0,0,0},
            {20,30,20,20,10,0,0,0,0,0},
            {5,10,30,10,0,0,0,0,0,0},
            {20,10,30,20,10,0,0,0,0,0},
            {15,30,20,40,10,20,0,0,0,0}
    }; //problem set
    p->push_back(0);
    for(int i = 0; i<10;i++){
        if(problem[t][i]!=0){
            p->push_back(problem[t][i]);
        }   
    }
}

void mcm(vector<int> *p, int n, int (*arr)[MAX_LEN],int (*small)[MAX_LEN]){
    
    int max = numeric_limits<int>::max();
    for(int i=1;i<=n;i++){
        arr[i][i] = 0;
    }

    for(int r=2;r<=n;r++){
        for (int i=1;i<=n-r+1;i++){
            int j = i+r-1;
            arr[i][j] = max;
            for(int k = i;k<=j-1;k++){
                int q = arr[i][k]+arr[k+1][j]+(p->at(i)*p->at(k+1)*p->at(j+1));
                if(q<arr[i][j]){
                    arr[i][j] = q;
                    small[i][j] = k;
                }
            }
            //printf("%d,%d,%d\t",i,j,arr[i][j]);
        }
    }
}

void print_optimal(int (*small)[MAX_LEN],int i,int j){
    if(i==j){
        printf("A[%d]",i);
    }else{
        printf("(");
        print_optimal(small, i, small[i][j]);
        print_optimal(small, small[i][j]+1, j);
        printf(")");
    }
}

