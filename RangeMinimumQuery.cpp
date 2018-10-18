#include <bits/stdc++.h>
using namespace std;
const int INF = 99999;
struct tree{
	int data;
	int leftIndex;
	int rightIndex;
};
int createRangeTree(int* arr, struct tree* treeArr, int st, int en, int current){ // current represents index in tree
	if(st == en){
		treeArr[current].data = arr[st];
		treeArr[current].leftIndex = st;
		treeArr[current].rightIndex = en;
		return arr[st];
	}
	else{
		int mid = (st + en)/2;
		int i = createRangeTree(arr, treeArr, st, mid, 2*current+1);
		int j = createRangeTree(arr, treeArr, mid+1, en, 2*current+2);
		if(i<j){
			treeArr[current].data = i;
			treeArr[current].leftIndex = st;
			treeArr[current].rightIndex = en;
			return i;
		}
		else{
			treeArr[current].data = j;
			treeArr[current].leftIndex = st;
			treeArr[current].rightIndex = en;
			return j;
		}
	}
}
int insertInTree(int* arr,struct tree* treeArr, int current, int insertIndex,int value){
	if(treeArr[current].leftIndex > insertIndex || treeArr[current].rightIndex < insertIndex){
		return INF;
	}
	else if(treeArr[current].leftIndex == insertIndex && treeArr[current].rightIndex == insertIndex){
		treeArr[current].data = value;
		return value;
	}
	else{
		int i = insertInTree(arr, treeArr, 2*current+1, insertIndex, value);
		int j = insertInTree(arr, treeArr, 2*current+2, insertIndex, value);
		if(i < j){
			treeArr[current].data = i;
			return i;
		}
		else{
			treeArr[current].data = j;
			return j;
		}
	}
}
int minRange(struct tree* treeArr, int current, int startIndex, int endIndex){
	int st = treeArr[current].leftIndex;
	int en = treeArr[current].rightIndex;
	if(st > endIndex || en < startIndex)
		return INF;
	else if( startIndex <= st && en <= endIndex ){
		return treeArr[current].data;
	}
	else{
		int i = treeArr[current].data, j = treeArr[current].data;
        if(treeArr[current].leftIndex != treeArr[current].rightIndex){
            i = minRange(treeArr, current*2+1, startIndex, endIndex);
            j = minRange(treeArr, current*2+2, startIndex, endIndex);
        }
		if(i<j)
			return i;
		else
			return j;
	}
}
int main(){
	int n;
	cin>> n;
	int* arr = new int[n];
	for(int i=0; i<n; i++)
		cin>>arr[i];
	struct tree* treeArr = new struct tree[2*n];
	for(int i=0; i<2*n; i++){
		treeArr[i].leftIndex = -1;
		treeArr[i].rightIndex = -1;
	}
	int dummy = createRangeTree(arr, treeArr, 0, n-1, 0);
	string s;
	cin>>s;
	while(s.compare("stop")!=0){
		if(s.compare("min")==0){
			int startIndex, endIndex;
			cin>>startIndex>>endIndex;
			cout<<"min: "<<minRange(treeArr, 0, startIndex, endIndex);
			cin>>s;
		}
		else if(s.compare("update")==0){ // update ith element of array
			int insertIndex, value;
			cin>>insertIndex>>value;
			arr[insertIndex] = value;
			int dummy2 = insertInTree(arr, treeArr, 0, insertIndex, value);
			cin>>s;
		}
	}
	return 0;
}