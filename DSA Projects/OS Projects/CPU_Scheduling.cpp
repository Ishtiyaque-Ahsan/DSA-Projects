/*

Taking pid , AT and BT and Priority of the processes as input
SJf Scheduling (Non-Preemptive) is implemented here
Priority Scheduling (Preemptive) is implemented here
Round Robin Scheduling  is implemented here

*/



#include <iostream>
#include<queue>
using namespace std;
void sort(int arr[15], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i-1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                
            }
        }
        
    }
}
int maxx(int prio[50], int k, int BT_temp[50], int np)
{
    int a = -6;
    int pr_idx = -2;
    int em = 0; // count no. of processes till time  = k
    for (int i = 0; i <= k; i++)
    {
        if (prio[i] != 0)
        {
            em++;
            if (prio[i] > a && BT_temp[i] != 0)
            {
                // for those index in priority array whose BT is not zero yet and have some priority > 0
                a = prio[i];
                pr_idx = i;
            }
        }
    }
    if (pr_idx == -2)
    { // if all the processes are executeed i.e. BT_temp[i]=0
        if (em == np)
            return -2;
        else
            return -10; // there are processes available after some time of rest
    }
    return pr_idx; // index of max priority process available is returned here
}
void print(int arr[15], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << "        ";
    }
    cout << endl;
}
// prints Burst Time
void printBT(int arr[50])
{
    for (int i = 0; i < 50; i++)
    {
        if (arr[i] != -1 && arr[i] != 0)
            cout << arr[i] << "        "; // print only those values of BT[] which have some nonvalue burst time value
    }
    cout << endl;
}
//prints Priority
void printpr(int arr[100])
{
    int i = 0;
    while (arr[i] != -1)
    {
        cout << arr[i] << "    ";
        i++;
    }
    cout << endl;
}
int minn(int BT_temp[50], int k){
    int a = 999;
    int minBT_temp_idx = -10;
    for(int i=0;i<=k;i++){
        if(BT_temp[i] < a && BT_temp[i]!=0 && BT_temp[i]!=(-1)){
            a = BT_temp[i];
            minBT_temp_idx = i; 
        }
    }
    return minBT_temp_idx;
}
// Shortest Job First (Non-Preemptive)
void SJF_Sch(int BT[50], int AT[15], int CT[15], int Pr[100], int np,int pid[50])
{
    int BT_temp[50]; // temp BT used to decrease BT of a process when its any portion is done
    for (int i = 0; i < 50; i++)
    {
        BT_temp[i] = BT[i];
    }
    int TimeNow = 0; // this will keep track of the time in gantt chart
    int k = 0;
    for(int i=0;i<np;i++){
        cout<<"Itedration "<<i+1<<endl;
        int process_AT = minn(BT_temp , k);//process_AT here is index of process in BT[] and its AT also
       // To resolve the case that if CPu sits idle for a moment
        if(process_AT == -10){  //CPU has no process to execute at this time = k        
            int s=k;
            while(BT_temp[s] <= 0){
                s++;
            }//now BT_temp[s] >0 and s is the arrival Time of next Process
            
            process_AT = s;
            TimeNow = s;
        } 
        int c=0;
        for (int j = 0; j <= process_AT; j++)
        {
            if(BT[j] > 0){
                c++;
            }
        } //c is number/name of process at index process_AT in BT[] 
        // c is  pid of executing process is pid is sequential according to AT
        c = c-1; //counting processes from P0
        cout<<"Process no. that has done is P"<<pid[process_AT]<<endl;
        Pr[i] = pid[process_AT];
        CT[c] = TimeNow + BT_temp[process_AT];
        cout<<"CT of this Process is "<<CT[c]<<endl;
        TimeNow = CT[c];
        cout<<"Time passed till now "<<TimeNow<<endl;
        k = CT[c];
        if( k >= 50 ){
            k = 49;
        }
        BT_temp[process_AT] = 0;
        cout<<endl;
    }

}
//Priority Scheduling (Preemptive)
void Priority_Sch(int BT[50], int AT[15], int Priority[50], int CT[15], int Pr[100], int np,int pid[50])
{
    int BT_temp[50]; // temp BT used to decrease BT of a process when its any portion is done
    for (int i = 0; i < 50; i++)
    {
        BT_temp[i] = BT[i];
    }
    int TimeNow = 0; // this will keep track of the time in gantt chart
    int k = 0;
    int count = 0; // no. of iterations or no. of blocks in gantt array
    // count is from 0 to CT of last process done increasing sequentially
    while (true)
    {

        int process_AT = maxx(Priority, k, BT_temp, np); // process_AT here is index of process in BT[] and Process's AT also
        if (process_AT == -2)                            // break out of loop if all the processes are completely executed i.e. BT_temp[i] = 0
            break;

        // To resolve the case that if CPu sits idle for a moment
        if (process_AT == -10)
        { // CPU has no process to execute at this time = k
            int s = k;
            while (BT_temp[s] <= 0)
            {
                s++;
            } // now BT_temp[s] >0 and s is the arrival Time of next Process
            process_AT = s;
            TimeNow = s;
        }
        cout << endl;
        int c = 0;
        for (int j = 0; j <= process_AT; j++)
        {
            if (BT[j] > 0)
            {
                c++;
            }
        }          // c is number/name of process at index process_AT in BT[]
        c = c - 1; // counting processes from P0
        cout << "Itedration " << count + 1 << endl;
        cout << "Process no. that has done is P" << pid[process_AT] << endl;
        Pr[count] = pid[process_AT]; // adding Process c in gantt array
        count++;
        BT_temp[process_AT]--;
        TimeNow++;
        if (BT_temp[process_AT] == 0)
        {
            CT[c] = TimeNow;
        }
        cout << "Time passed till now " << TimeNow << endl;
        k = TimeNow;
        if (k >= 50)
        {
            k = 49;
        }
    }
}
//Round Robin
void RoundRobin_Sch(int BT[50], int AT[15], int TQ, int CT[15], int Pr[100], int np , int pid[50]){
    int BT_temp[50]; // temp BT used to decrease BT of a process when its any portion is done
    for (int i = 0; i < 50; i++)
    {
        BT_temp[i] = BT[i];
    }
    int TimeNow = 0; // this will keep track of the time in gantt chart
    int k = 0;
    queue<int> q;
     int e=0; //index to push processes in queue P0 , P1 , ...(initial pushes of all processes)
    
    int pr_exe=0;  // name of process being poped from queue and executing
    int pr_idx = 0 ; //sequential index in Pr array
    int process_AT = AT[0];
    q.push(0); //pushed P0 in queue and it will exxecute
    TimeNow = AT[0];
    e++;
    int Process_id = 0;
    while (!q.empty())
    {   
            
        pr_exe = q.front();  //front element in queue (pr_exe) is poped and it will execute
        q.pop();
        
        Process_id = pid[AT[pr_exe]]; //pr_exe is the pid of executing process of pid is sequential
        Pr[pr_idx] = Process_id;
        cout << "Process no. that has done is P" << Process_id << endl;
        process_AT = AT[pr_exe];
        
        if(BT_temp[process_AT] >= TQ){
            TimeNow+=TQ;
            BT_temp[process_AT] -= TQ; 
        }
        else{
            
            TimeNow += BT_temp[process_AT];
            BT_temp[process_AT] = 0; 
        }
            

        cout << "Time passed till now " << TimeNow << endl;
       
        while(AT[e] <= TimeNow && e<np){
            q.push(e);
          //  cout<<"Process-"<<e<<" is pushed in queue at Time- "<<TimeNow<<endl;
            e++;
        }
        
        if (BT_temp[process_AT] > 0)
        {
            q.push(pr_exe);
          //  cout<<"Process-"<<pr_exe<<" is pushed in queue at Time- "<<TimeNow<<endl<<endl;
        }     
        if (BT_temp[process_AT] == 0)
        {
            CT[pr_exe] = TimeNow;
        }
        pr_idx++;
        
        // To resolve the case that if CPU sits idle for a moment
        if(q.empty() && e<np ){   // not all np processes are started for their execution
            // CPU has no process to execute at this time = TimeNow        
            int s = TimeNow;
            while(BT_temp[s] <= 0){
                s++;
            }//now BT_temp[s] >0 and s is the arrival Time of next Process
           
           // process_AT = s;
            TimeNow = s;
            q.push(e);
            e++;
        }       
    }
}

int main()
{
    int np = 6;
    cout<<"Enter number of processes : ";
    cin>>np;
    
    int TQ = 2;
    cout<<"\nEnter Time Quantum for Round Robin  : ";
    cin>>TQ;

    int AT[15] = {0};
    int pid[50] = {0};
    for (int i = 0; i < 50; i++)
    {
        pid[i] = -1;
    }
    int BT[50] = {0};      // burst time is taken at index = Arrival_Time of of that process
    int Priority[50] = {0}; // Priority is taken at index = Arrival_Time of of that process
    //assuming max AT = 50
    // cout<<"\nEnter Arrival Time & Priority & Burst Time (BT) of the processes : \n";
    //  for (int i = 0; i < np; i++){
    //      cin>>AT[i];
    //      cin>>pid[AT[i]];
    //      cin>>Priority[AT[i]];
    //      cin>>BT[AT[i]];      
    //  }

    
    AT[0] = 4;
    AT[1] = 3;
    AT[2] = 8;
    AT[3] = 0;
    AT[4] = 6;
    AT[5] = 1;

    pid[4] = 1;
    pid[3] = 2;
    pid[8] = 3;
    pid[0] = 4;
    pid[6] = 5;
    pid[1] = 6;

    BT[4] = 8;
    BT[3] = 3;
    BT[8] = 5;
    BT[0] = 6;
    BT[6] = 2;
    BT[1] = 4;

    Priority[4] = 1;
    Priority[3] = 2;
    Priority[8] = 3;
    Priority[0] = 4;
    Priority[6] = 5;
    Priority[1] = 6;

    sort(AT, np);

    cout<<endl<<"Printing the given input in formatted form : "<<endl;
    cout<<"  Process-id   AT    Priority       BT "<<endl;
    for (int i = 0; i < np; i++)
    {

        cout<<"     "<<pid[AT[i]]<<"           "<<AT[i]<<"       "<<Priority[AT[i]]<<"        "<<BT[AT[i]]<<endl;
    }
    

    cout<<endl;
    int CT[15] = {0};
    int TAT[15] = {0};
    int WT[15] = {0};
    int Process_Gantt[100] = {0}; // array for storing sequence of processes in execution - gantt array
    for (int i = 0; i < 100; i++)
    {
        Process_Gantt[i] = -1;
    }
   
    for (int z = 0; z < 3; z++)
    {
        if(z == 0){
            cout<<"\nApplying SJF (Non-Preemptive) Scheduling : \n";
            SJF_Sch(BT, AT, CT, Process_Gantt, np,pid);
        }
        if(z == 1){
            cout<<"\n\nApplying Priority (Preemptive) Scheduling : \n";
            Priority_Sch(BT, AT, Priority, CT, Process_Gantt, np,pid);
        }
        if(z == 2){
            cout<<"\n\nApplying Round-Robin Scheduling : \n";
            RoundRobin_Sch(BT, AT, TQ, CT, Process_Gantt, np,pid);
        }
        float avgTAT = 0;
        float avgWT = 0;
        for (int i = 0; i < np; i++)
        {
            TAT[i] = ((CT[i]) - (AT[i]));
            avgTAT += TAT[i];
        }

        for (int i = 0; i < np; i++)
        {
            WT[i] = ((TAT[i]) - (BT[AT[i]]));
            avgWT += WT[i];
        }
        float avgt = avgTAT / np;
        float avgw = avgWT / np;

        cout << "Printing Processes array :  ";
        for (int i = 0; i < 50; i++)
        {
             if (pid[i] != -1 )
                cout << pid[i] << "        "; // print only those values of BT[] which have some nonvalue burst time value
        }
         cout << endl;
        cout << "\nPrinting AT array :         ";
        print(AT, np);
        cout << "Printing BT array :         ";
        printBT(BT);
        cout << "Printing CT array :         ";
        print(CT, np);
        cout << "Printing TAT array :        ";
        print(TAT, np);
        cout << "Printing WT array :         ";
        print(WT, np);

        cout << "Avg TAT is : " << avgt << "   Avg WT is : " << avgw << endl;
        cout << "\nPrinting Processes execution Sequence in Gantt Array :  \n"; // gantt array
        printpr(Process_Gantt);
        
        for(int y=0;y<100;y++){ //for resetting CT[] and Process_Gantt[] array for next schedulings
            if(y<15){
                CT[y] = 0;
            }
            Process_Gantt[y] = -1;
        }
    }
    return 0;
}