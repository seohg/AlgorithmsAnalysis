#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>

#define SEED 5
using namespace std;

void generate_array(vector<int> *arr, int size); // generate array
void print_array(vector<int> *arr, int size); // print generated array

void insertion_sort(vector<int> *res, int size); //Insertion sort

void heap_sort(vector<int> *res, int size); // Heap Sort
void build_max_heap(vector<int> &res, int size); //build max heap (Heap Sort)
void max_heapify(vector<int> &res, int parent, int size); //reconstruct the heap.

void quick_sort(vector<int> &res, int start, int end);// Quick sort
int partition(vector<int> &res, int start, int end); // partition (Quick sort)


int main(){
    vector<int> arr; 
    vector<int> res;

    /* for calculating running time ( 1clock = 1ms ) */
    clock_t i_start, i_end;
    clock_t h_start, h_end;
    clock_t q_start, q_end;

    for(int i=1; i<=10;i++){
        printf("======== Array Size : %d =========\n",i*10); // print array size
        generate_array(&arr,i*10); //generate array
        print_array(&arr,i*10); //print generated array
        printf("\n");

        /* insertion sort */
        i_start = clock();
        res.resize((int)(arr.size()));
        copy(arr.begin(),arr.end(),res.begin()); //copy array to result vector
        insertion_sort(&res, i*10); //insertion sort
        i_end = clock();

        printf("insertion sort result\n");
        print_array(&res,i*10); //print result of insertion sort
        printf("running time: %lfms\n\n",(double)(i_end - i_start)); //caculate run time
        res.clear(); //clear result vector

        /* Heap sort */
        h_start = clock();
        res.resize((int)(arr.size()));
        copy(arr.begin(),arr.end(),res.begin()); //copy array to result vector
        heap_sort(&res, i*10); // Heap Sort
        h_end = clock();

        printf("heap sort result\n");
        print_array(&res,i*10); //print result of heap sort
        printf("running time: %lfms\n\n",(double)(h_end - h_start)); //caculate run time
        res.clear(); //clear result vector

        /* Quick sort */
        q_start = clock();
        res.resize((int)(arr.size()));
        copy(arr.begin(),arr.end(),res.begin()); //copy array to result vector
        quick_sort(res,0, i*10-1); // quick Sort
        q_end = clock();

        printf("quick sort result\n");
        print_array(&res,i*10); //print result of quick sort
        printf("running time: %lfms\n\n",(double)(q_end - q_start)); //caculate run time
        res.clear(); //clear result vector

        arr.clear(); //clear vector
        printf("\n\n");
    }
    return 0;
}

/* generate array */
void generate_array(vector<int> *arr, int size){

    srand(SEED * size); //set random seed (seed * size) 

    for(int i=0; i<size; i++){ //iterate as size
        int r = rand()%500+1; //range = [1,500]
        arr->push_back(r); //save random number in vector
    }
}

/* print generated array */
void print_array(vector<int> *arr, int size){
    printf("[");
    for(int i=0; i<size; i++){
        printf("%d",arr->at(i)); //print elements
        if(i!=size-1){
            printf(",");
        }else{
            printf("]\n");
        }
    }
}

/* Insertion Sort */
void insertion_sort(vector<int> *res, int size){
    int j, key;

    for(int i=1; i<size; i++){
        key = res->at(i); 
        for(j=i-1; j>=0; j--){
            if(res->at(j) > key){ //if value is bigger than key 
                res->at(j+1) = res->at(j); //move the value to index+1
            }else{
                break; //if not exit the loop
            }
        }
        res->at(j+1) = key; //move key to proper position
    }
}

/* Heap Sort */
void heap_sort(vector<int> *res, int size){
    build_max_heap(*res, size); //build max heap
    
    for(int i=size-1;i>=0;i--){
        swap(res->at(0),res->at(i)); //swap top node and last node
        size--; 
        max_heapify(*res,0,size); // reconstruct the remained heap 
    }
}

void build_max_heap(vector<int> &res, int size){ //make array to heap
    for(int i = size/2-1; i>=0; i--){
        max_heapify(res,i,size); //make heap from the bottom 
    }
}

void max_heapify(vector<int> &res, int parent, int size){ //reconstruct heap
    int left, right, max;
    max = parent;
    left = parent * 2;
    right = parent * 2 + 1;
    /* find the max among parent, left child, right child */
    if(left<size && res.at(left) > res.at(max)){
        max = left;
    }
    if(right<size && res.at(right) > res.at(max)){
        max = right;
    }
    if(max != parent){ //if max value is not parent value
        swap(res.at(parent),res.at(max)); //swap max value to parent position
        max_heapify(res,max,size); //reconstruct the child's heap
    }
}

/* Quick sort */
void quick_sort(vector<int> &res, int start, int end){
    if(start<end){
        int pivot = partition(res, start, end); //recieve pivot
        quick_sort(res,start,pivot-1); // left part of pivot
        quick_sort(res,pivot+1,end); // right part of pivot
    }
}

int partition(vector<int> &res, int start, int end){ // return the pivot's index
    int pivot = res.at(end); //set last element to pivot
    int i = start - 1;
    for(int j = start; j < end; j++){
        if(res.at(j)<=pivot){ // if j's value is same or less than pivot
            i = i+1;
            swap(res.at(i),res.at(j)); //swap the value to i's value
        }
    }
    swap(res.at(i+1),res.at(end)); //swap the last element value and i+1's value
    return i+1; //return pivot's index
}
