#include <iostream>
#include <string.h>
#include <stdlib.h> 
#include <cstdio>
#include <ctime>
using namespace std;

/* sturctures for BFS */
typedef struct Node{ //Node for BFS
    int mat[3][3]; // puzzle board
    int row, col; //position of zero
    Node *parent; // link parent node
}Node;

typedef struct qNode{ //Node for BFS queue
    struct Node* qnode; //node structure
    struct qNode* next;  //for link nodes
}qNode;

typedef struct Vector{ //this is simple vector structure for storing path
    Node* vnode; //node 
    Vector* next; //link
}Vector;

/* queue (data structure) using class*/
class queue{
    qNode *front, *rear; //link head & tail
public:
    queue();        //constructure
    void insert_q(Node*t);  //insert node
    void delete_q(); //delete node 
    Node* queue_front();  //show front node
    bool queue_empty();  //check queue is empty or not
};

queue::queue(){
    front=NULL; //init front
    rear=NULL;  //init tail
}

void queue::insert_q(Node* t){ 
    qNode* temp = new qNode; //make new qNode
    temp->qnode = t; //store node
    temp->next = NULL; //init link ptr as null

    if(rear==NULL){  //if node is frist node    
        rear = temp; // tail ptr -> new qNode
        front = temp;  // head ptr -> new qNode
        return;
    }
    rear->next = temp; //if node is not first node
    rear=temp;  //push new qNode in back
}

void queue::delete_q(){
    if(!queue_empty()){ // queue is not empty
        qNode* tmp = front; //store the front node temporary 
        front=front->next; //move front ptr to next node

        if(front==NULL){ //if there is no next node
            rear=NULL; //make tail ptr to null
        }
        
        delete tmp; //delete node
    }
}

Node* queue::queue_front(){
    if(!queue_empty()){ //if queue is not empty
        Node* temp = new Node; //make new Node 
        temp = front->qnode; //store front node to temp temporary
   
        return temp; //return temp node
    }
    return NULL; //if queue is empty, return null
}

bool queue::queue_empty(){
    if(front==NULL&&rear==NULL){ //if head, tail ptr is null
        return true; //return true
    }else{
        return false; // if not, return false
    }
}

/* target matrix */
int output[3][3] = {{1,2,3},{8,0,4},{7,6,5}}; 

/* functions */
void init_node(Node* node); //initiallize node
void get_matrix(Node* node); //get input matrix
void print_node(Node* node); //print node's matrix
bool compare(int cur[][3], int out[][3]); //compare the matrix
void b_move(Node* node); //make child node (moving zero)
void move_up(Node* node);//move zero to upside
void move_down(Node* node);//move zero to downside
void move_left(Node* node);//move zero to left
void move_right(Node* node); //move zero to right
void copy_node(Node* newNode, Node* orgNode); //copy nodes (deepcopy)
bool is_exist(Node* node); //check if there is same node in parent(path)
void procedure(Node* node); //print path

int BFS(Node* node); //for BFS

/* global */
queue q; //for queue
Vector* path_head = new Vector; //for saving path(head)
Vector* path = new Vector; //for saving path (other nodes)

int main(){
    struct Node* node = new Node; //make root node for DFS
    clock_t startTime, endTime;
    init_node(node); //init root node
    get_matrix(node); //recieved value of matrix (save position of zero)

    startTime = clock();
    BFS(node); //solve puzzle using bfs
    endTime = clock();

    cout<<"running time : "<<double(endTime - startTime)/CLOCKS_PER_SEC<<"s"<<endl;
    return 0;
}

/* compare current node matrix to target matrix */
bool compare(int cur[][3], int out[][3]){
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(cur[i][j]!=out[i][j]){
                return false;
            }
        }
    }
    return true;
}

/* init node */
void init_node(Node* node){
    for(int i=0 ;i<3 ;i++){
        for(int j=0 ;j<3 ;j++){
            node->mat[i][j] = 0;
        }
    }
    node->row=0; 
    node->col=0;
    node->parent = NULL;
}

/* get matrix */
void get_matrix(Node* node){
    for(int i=0 ;i<3 ;i++){
        for(int j=0 ;j<3 ;j++){
            int temp;
            scanf("%d",&temp);  //get matrix element
            node->mat[i][j] = temp; 
            if(temp == 0){
                node->row = i;
                node->col = j;
            }
        } 
    }        
}

/* print node */
void print_node(Node* node){
    if(node!=NULL){
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                printf("%d\t",node->mat[i][j]);
            }
            printf("\n");
        }
    }
}

/* print procecure (path) */
void procedure(Node* node){
    int a = 0; // for printing step number
    struct Node* parent = node; 

    path_head->next = path; //link path_head and path

    path->vnode=parent; //save path's node
    path->next = NULL; //init link ptr as null
    
    
    while(parent!=NULL){ //exit if node is root node
        Vector* temp = new Vector;
        a--;
        parent = parent->parent; //load parent node

        path->next = temp; //link new node to vector

        temp->vnode = parent; //save parent to node
        temp->next = NULL; //init ptr as null

        if(parent==NULL){
            break;
        }

        printf("\n[%d]=============\n",a); 
        print_node(temp->vnode);
        printf("==================\n");
        
    }
    

}

/* move zero */
void move_up(Node* node){ 
    node->mat[node->row][node->col] = node->mat[node->row-1][node->col];
    node->mat[node->row-1][node->col]=0;
    node->row = node->row-1;
}
void move_down(Node* node){
    node->mat[node->row][node->col] = node->mat[node->row+1][node->col];
    node->mat[node->row+1][node->col]=0;
    node->row = node->row+1;
}
void move_left(Node* node){
    node->mat[node->row][node->col] = node->mat[node->row][node->col-1];
    node->mat[node->row][node->col-1]=0;
    node->col = node->col-1;
}
void move_right(Node* node){
    node->mat[node->row][node->col] = node->mat[node->row][node->col+1];
    node->mat[node->row][node->col+1]=0;
    node->col = node->col+1;
}

void b_move(Node* node){ 

    for(int i=0;i<4;i++){ //up, down, right, left
        struct Node *newNode = new Node; //for child node
        copy_node(newNode, node); //copy the origin node
        newNode->parent = node; //link the origin node as parent

        switch(i){
            case 0:
                if(newNode->row!=0){ 
                    move_up(newNode); // in child node modify the position of zero to upside
                    if(!is_exist(newNode)){ //if modified node is not same with any parent(in path) node
                        q.insert_q(newNode); //insert this node to queue
                    }

                }
                break;

            case 1:
                if(newNode->row!=2){
                    move_down(newNode);
                    if(!is_exist(newNode)){
                        q.insert_q(newNode);
                    }
                }
                break;
            case 2:
                if(newNode->col!=0){
                    move_left(newNode);
                    if(!is_exist(newNode)){
                        q.insert_q(newNode);
                    }
                }
                break;
            case 3:
                if(newNode->col!=2){
                    move_right(newNode);
                    if(!is_exist(newNode)){
                        q.insert_q(newNode); 
                    }
                }
                break;
            default:;
                
        }   
    }
}

/* check whether the node is same with parent node */
bool is_exist(Node* node) { 
  struct Node* temp = node->parent;
  while(temp!= NULL) {
      
    if(compare(node->mat, temp->mat)) { //if there is same matrix
        return true; //return true
    } 
    temp = temp->parent;
  }
  return false;
}

/* copy node*/
void copy_node(Node* newNode, Node* orgNode){ //copy node's element
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            newNode->mat[i][j] = orgNode->mat[i][j];
        }
    }
    newNode->row=orgNode->row; 
    newNode->col=orgNode->col;
    newNode->parent =NULL;
    
}

/***** BFS algorithm *****/
 int BFS(Node* node){
    struct Node* current_node = new Node; 

    q.insert_q(node); //push root node

    while(!q.queue_empty()){ //iterate until queue is empty or find solution
        current_node = q.queue_front(); //load front node
        q.delete_q(); //delete loaded node
       
        if(compare(current_node->mat, output)){ //if it find solution
            printf("===== ANSWER =====\n");
            print_node(current_node);
            procedure(current_node); //save path
           
            return 1;
        }
        
        b_move(current_node); //make new node and move zero (child node)
    }
    return 0;
}