//sjf scheduling algorithm
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
    int n,i,j,k,l;
    cout<<"******SJF SCHEDULING ALGORITHM******\n"<<endl;;
    cout<<"Enter The Number Of Processes : ";
    cin>>n;
    PROCESS P[n],Q[n],R[n];
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

    //Assign same first arrival time to new Process

    double at = P[0].AT;
    PROCESS Z[n];
    int t = 0;
    while(at==P[t].AT) {
        Z[t] = P[t];
        t++;
    }

    //Sorting First arrival Processes(Burst Time)

    if(t-1!=0) {
        for(i=0;i<t-1;i++){
            for(j=0;j<t-i-1;j++){
                if(Z[j].BT>Z[j+1].BT){
                    PROCESS temp4 = Z[j];
                    Z[j]=Z[j+1];
                    Z[j+1]=temp4;
                }
            }
        }
    }

    //Assign Sorted Burst Time To Main Queue

    for(i=0;i<t;i++){
        P[i]=Z[i];
    }
	//Starting Time And Waiting Time Calculation

    for(i=0;i<n;i++) {
        if(i==0){
           P[i].ST = P[i].AT;
           P[i].ET = (P[i].ST+P[i].BT);
           P[i].WT = P[i].ST-P[i].AT;
           P[i].TT = (P[i].ET-P[i].AT);
           R[i] = P[i];
        } else {

            k = 0;
        for(j=i;j<n;j++) {
            if(P[j].AT<R[i-1].ET){
                Q[k]=P[j];
                k++;
            }
        }

        for(j=0;j<k;j++){
            for(l=0;l<k-j-1;l++){
                if(Q[l].BT>Q[l+1].BT){
                    PROCESS temp1 = Q[l];
                    Q[l] = Q[l+1];
                    Q[l+1] = temp1;
                }
            }
        }
        R[i] = Q[0];
        R[i].ST = R[i-1].ET;
        R[i].ET = (R[i].ST+R[i].BT);
        R[i].WT = R[i].ST-R[i].AT;
        R[i].TT = (R[i].ET-R[i].AT);


        for(int j=i;j<n;j++){
            if((Q[0].AT==P[j].AT)&&(Q[0].BT==P[j].BT)){
                PROCESS temp3 = P[j];
                P[j] = P[i];
                P[i] = temp3;
            }

        }
        }
    }

    cout<<"\nProcess ID\tStarting Time\tWaiting Time\tTurn Around Time"<<endl;
    for(i=0;i<n;i++) {
        R[i].dispT();
    }
    double avgWT=0,avgTT=0;

    for(i=0;i<n;i++) {
        avgWT = R[i].WT + avgWT;
    }

    for(i=0;i<n;i++) {
        avgTT = R[i].TT + avgTT;
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
        cout<<"|  "<<R[i].PID<<"\t ";
    }
    cout<<"|"<<endl;
    for(i=0;i<n-1;i++) {
        cout<<R[i].ST<<"-----\t";
    }
    cout<<R[n-1].ST<<"-----"<<R[n-1].ET<<endl;
    return 0;
}
//starting-> ST=0 , next-> ST=ST+BT
//WT=ST-AT
//TT=(ST+BT)-AT
//:D MaxySpark :D
