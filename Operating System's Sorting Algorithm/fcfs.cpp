//fcfs scheduling algorithm
#include<iostream>
using namespace std;
class PROCESS {
    public:
    char PID[10];
    double AT,BT,ST,ET,WT,TT;
    void getData();
    void disp();
    void dispT();
};

void PROCESS :: getData() {
    cout<<"Enter Process Id : ";
    cin>>PID;
    cout<<"Enter Arrival Time For Process "<<PID<<" : ";
    cin>>AT;
    cout<<"Enter Burst Time For process "<<PID<<" : ";
    cin>>BT;
}

void PROCESS :: disp(){
    cout<<"  "<<PID<<"\t\t  "<<AT<<"\t\t  "<<BT<<endl;
}

void PROCESS :: dispT(){
    cout<<"  "<<PID<<"\t\t  "<<ST<<"\t\t  "<<WT<<"\t\t  "<<TT<<endl;
}

int main()
{
    int n,i,j;
    cout<<"******FCFS SCHEDULING ALGORITHM******\n"<<endl;;
    cout<<"Enter The Number Of Processes : ";
    cin>>n;
    PROCESS P[n];
    for(i=0;i<n;i++){
            cout<<endl;
        P[i].getData();
    }

    cout<<"\nProcess ID\tArrival Time\tBurst Time"<<endl;
    for(i=0;i<n;i++) {
        P[i].disp();
    }

    //Sorting Processes By Arrival Time

    for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(P[j].AT>P[j+1].AT)
			{
				PROCESS temp=P[j];
				P[j]=P[j+1];
				P[j+1]=temp;
			}
		}
	}

	//Starting Time And Waiting Time Calculation

    for(i=0;i<n;i++) {
        if(i==0){
           P[i].ST = P[i].AT;
        } else {
        P[i].ST = P[i-1].ET;
        }
        P[i].ET = (P[i].ST+P[i].BT);
        P[i].WT = P[i].ST-P[i].AT;
        P[i].TT = (P[i].ET-P[i].AT);
    }

    cout<<"\nProcess ID\tStarting Time\tWaiting Time\tTurn Around Time"<<endl;
    for(i=0;i<n;i++) {
        P[i].dispT();
    }
    double avgWT=0,avgTT=0;

    for(i=0;i<n;i++) {
        avgWT = P[i].WT + avgWT;
    }

    for(i=0;i<n;i++) {
        avgTT = P[i].TT + avgTT;
    }
    float a,aWT,aTT;
    a = float(n);
    aWT = float(avgWT);
    aTT = float(avgTT);
    aWT= aWT/a;
    aTT= aTT/a;
    cout<<"\nAverage Waiting Time = "<<aWT<<endl;
    cout<<"\nAverage Turn Around Time = "<<aTT<<endl;

    cout<<"\n- - Gantt Chart - -"<<endl;
    //GANTT CHART

    for(i=0;i<n;i++) {
        cout<<"--------";
    }
    cout<<"-"<<endl;
    for(i=0;i<n;i++) {
        cout<<"|  "<<P[i].PID<<"\t ";
    }
    cout<<"|"<<endl;
    for(i=0;i<n-1;i++) {
        cout<<P[i].ST<<"-----\t";
    }
    cout<<P[n-1].ST<<"-----"<<P[n-1].ET<<endl;
    return 0;
}
//starting-> ST=0 , next-> ST=ST+BT
//WT=ST-AT
//TT=(ST+BT)-AT
//:D MaxySpark :D
