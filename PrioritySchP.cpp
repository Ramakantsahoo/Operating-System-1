/* Priority Preemptive */
#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

struct Process{
	int pid, pr, arr, bt;	
};

int comp(const void* P1, const void* P2){
	int t1 = ((Process *)P1) -> arr;
	int t2 = ((Process *)P2) -> arr;
	return t1 - t2;
}

void PrintProc(Process P[], int n, int comp[], int tat[], int wt[]){
	cout<<"PID\tPr\tArr\tBt\tComp\tTAT\tWT"<<endl;
	for(int i = 0; i < n; i++)
		cout<<P[i].pid<<"\t"<<P[i].pr<<"\t"<<P[i].arr<<"\t"<<P[i].bt<<"\t"<<comp[i]<<"\t"<<tat[i]<<"\t"<<wt[i]<<endl;
}

void evaluateTimePrP(Process P[], int n, float & av_WT, float & av_TAT){
	qsort(P, n, sizeof(P[0]), comp);
	vector<int> Gantt;
	int rem[n], comp[n], tat[n], wt[n];
	for(int i = 0; i < n; i++)
		rem[i] = P[i].bt;
	int n_cmp = 0, mpp, t = P[0].arr, priority = P[0].pr;
	while(n_cmp < n){
		for(int i = 0; i < n; i++)
			if(P[i].pr > priority && rem[i] && P[i].arr <= t){
				mpp = i;
				priority = P[i].pr;
			}
		t++;
		rem[mpp]--;
		Gantt.push_back(P[mpp].pid);
		if(!rem[mpp]){
			comp[mpp] = t;
			n_cmp++;
		}
		priority = INT_MIN;
	}
	for(int i = 0; i < n; i++){
		tat[i] = comp[i] - P[i].arr;
		wt[i] = tat[i] - P[i].bt;
		av_WT += (float)wt[i];
		av_TAT += (float)tat[i];
	}
	av_WT /= (float)n;
	av_TAT /= (float)n;
	cout<<"Gantt Chart: | ";
	for(auto Proc : Gantt)
		cout<<Proc<<" | ";
	cout<<endl;
	PrintProc(P, n, comp, tat, wt);
}

int main(){
	int n;
	cout<<"Enter the number of Processes: ";
	cin>>n;
	Process P[n];
	cout<<"Enter the Process ID, Priority, Arrival Time and Burst Time"<<endl;
	for(int i = 0; i < n; i++){
		cout<<"S.N."<<(i + 1)<<": ";
		cin>>P[i].pid>>P[i].pr>>P[i].arr>>P[i].bt;
	}
	float av_WT = 0, av_TAT = 0;
	evaluateTimePrP(P, n, av_WT, av_TAT);
	cout<<"\nAverage Waiting Time: "<<av_WT;
	cout<<"\nAverage Turn Around Time: "<<av_TAT<<endl;
	return 0;
}

/* TERMINAL
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/OS_LAB$ g++ -o PrioritySchP.exe ./PrioritySchP.cpp
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/OS_LAB$ ./PrioritySchP.exe 
Enter the number of Processes: 4
Enter the Process ID, Priority, Arrival Time and Burst Time
S.N.1: 1 10 0 5
S.N.2: 2 20 1 4
S.N.3: 3 30 2 2
S.N.4: 4 40 4 1
Gantt Chart: | 1 | 2 | 3 | 3 | 4 | 2 | 2 | 2 | 1 | 1 | 1 | 1 | 
PID	Pr	Arr	Bt	Comp	TAT	WT
1	10	0	5	12	12	7
2	20	1	4	8	7	3
3	30	2	2	4	2	0
4	40	4	1	5	1	0

Average Waiting Time: 2.5
Average Turn Around Time: 5.5

*/
