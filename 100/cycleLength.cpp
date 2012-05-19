#include <iostream>
using namespace std;
int cycleLengths(int,int);
int findCycleLength(int);

int main(int argc, char* argv[]){
	int i,j;
	cin>>i;
	cin>>j;
	int max=cycleLengths(i,j);
	cout<<i<<" "<<j<<" "<<max<<endl;
	return 0;
}

int cycleLengths(int begin,int end){
	int max=0;
	for(int i=begin;i<=end;i++){
		int n = findCycleLength(i);
		if(n>max) 
			max=n;	
	}
	return max;
}

int findCycleLength(int n){
	int count=1;
	if(n==1)
		return count;
	else if(n%2!=0)
		count+=findCycleLength(3*n+1);
	else
		count+=findCycleLength(n/2);
	return count;
}
