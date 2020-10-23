#include<bits/stdc++.h>
using namespace std;

void buildTree(int* arr,int* tree,int start,int end,int index){
    if(start == end){
        tree[index] = arr[start];
        return;
    }
    int mid = start+(end-start)/2;
    buildTree(arr,tree,start,mid,index*2);
    buildTree(arr,tree,mid+1,end,(index*2)+1);
    tree[index] = min(tree[(index*2)+1],tree[index*2]);
}

void updateTree(int* arr,int* tree,int start,int end,int index,int x,int y){
    if(start == end){
        arr[x] = y;
        tree[index] = y;
        return;
    }
    int mid = start + (end-start)/2;
    if(x>mid){
        updateTree(arr,tree,mid+1,end,(index*2)+1,x,y);
    }
    else{
        updateTree(arr,tree,start,mid,(index*2),x,y);
    }
    tree[index] = min(tree[index*2],tree[(index*2)+1]);
}

int queryTree(int* tree,int start,int end,int index,int x,int y){
    if(start>y || end<x){
        return INT_MAX;
    }
    if(start>=x && end<=y){
        return tree[index];
    }
    int mid = start + (end-start)/2;
    int ans1 = queryTree(tree,start,mid,2*index,x,y);
    int ans2 = queryTree(tree,mid+1,end,(2*index)+1,x,y);
    return min(ans1,ans2);
}

int main() {

	// Write your code here
    int n,q;
    cin >> n >> q;
    int* arr = new int[n];
    for(int i=0;i<n;i++){
        cin >> arr[i];
    }
    int* tree = new int[4*n];
    buildTree(arr,tree,0,n-1,1);
    // for(int i=1;i<4*n;i++){
    //     cout << tree[i] << " ";
    // }
    // cout << endl;
    for(int i=0;i<q;i++){
        char query;
        int x,y;
        cin >> query >> x >> y;
        if(query == 'q'){
            int ans = queryTree(tree,0,n-1,1,x-1,y-1);
            cout << ans << endl;
        }
        else{
            updateTree(arr,tree,0,n-1,1,x-1,y);
            // for(int i=1;i<4*n;i++){
            //     cout << tree[i] << " ";
            // }
            // cout << endl;
        }
    }
    delete[] arr;
    delete [] tree;
    return 0;
}