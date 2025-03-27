/*

MLQ CPU Scheduling is implemented here
System Proceses -> Round Robin 
Interactive Proceses -> Round Robin 
Background Proceses -> FCFS 
Here Greater Number has higher Priority

*/
#include <iostream>
#include <queue>
using namespace std;
void print(int arr[15], int n)
{
    for (int i = 0; i < n; i++)
    {
        // cout << arr[i] << "   ";
        if ((arr[i] / 10) == 0)
            cout << arr[i] << "   ";
        if ((arr[i] / 10) >= 1)
            cout << arr[i] << "  ";
    }
    cout << endl;
}
void printprbreif(int arr[100])
{
    int a = -1;
    int i = 0;
    cout << "         ";
    while (arr[i] != -1)
    {
        if (arr[i] != a)
        {
            cout << arr[i] << "  |  ";
        }
        a = arr[i];
        i++;
    }
    cout << endl;
}
void printpr(int arr[100])
{
    int i = 0;
    cout << " ";
    while (arr[i] != -1)
    {
        cout << arr[i] << " |";
        i++;
    }
    cout << endl;
}
void printBT(int arr[50])
{
    for (int i = 0; i < 50; i++)
    {
        if (arr[i] != -1 && arr[i] != 0)
            // cout << arr[i] << "   "; // print only those values of BT[] which have some nonvalue burst time value
            if ((arr[i] / 10) == 0)
                cout << arr[i] << "   ";
        if ((arr[i] / 10) >= 1)
            cout << arr[i] << "  ";
    }
    cout << endl;
}
void sort(int arr[15], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}


int main()
{
    int np = 8;
    cout<<"Enter number of processes : ";
    cin>>np;
    int AT[15] = {0};
    int pid[50] = {0};
    int BT[50] = {0};
    int cat_prio[50] = {0}; // it will store the cat_priority of a process as 1,2,3 at index=AT

    cout<<"\nEnter Arrival Time & BT & category Priority of the processes : \n";
     for (int i = 0; i < np; i++){
         cin>>AT[i];
         cin>>BT[AT[i]]; 
         cin>>cat_prio[AT[i]];     
     }
    // AT[0] = 0;
    // AT[1] = 3;
    // AT[2] = 4;
    // AT[3] = 7;
    // AT[4] = 8;
    // AT[5] = 13;
    // AT[6] = 15;
    // AT[7] = 28;

    // BT[0] = 6;
    // BT[3] = 2;
    // BT[4] = 3;
    // BT[7] = 4;
    // BT[8] = 5;
    // BT[13] = 2;
    // BT[15] = 3;
    // BT[28] = 6;

    // cat_prio[0] = 3; // system process
    // cat_prio[3] = 1; // background process
    // cat_prio[4] = 2; // interactive process
    // cat_prio[7] = 3;
    // cat_prio[8] = 3;
    // cat_prio[13] = 1;
    // cat_prio[15] = 2;
    // cat_prio[28] = 2;

    sort(AT, np);
    // giving sequential pid to processes based on AT as pid =0,1,2,3,...
    for (int i = 0; i < np; i++)
    {
        pid[AT[i]] = i;
    }
    cout<<"Cat_prio is category priority which is higher for higher priority queues\n";
    cout<<"cat_prio value is : 3 for system process , 2 for interactive process , 1 for background process\n ";
    cout << endl
         << "Printing the given input in formatted form : " << endl;
    cout << "  Process-id   --AT--       --BT--        Cat_prio " << endl;
    for (int i = 0; i < np; i++)
    {
        cout << "     " << pid[AT[i]] << "            " << AT[i] << "           " << BT[AT[i]]<< "           " << cat_prio[AT[i]] << endl;
    }

    int BT_temp[50]; // temp BT used to decrease BT of a process when its any portion is done
    for (int i = 0; i < 50; i++)
    {
        BT_temp[i] = BT[i];
    }
    cout << endl;

    int CT[15] = {0};
    int TAT[15] = {0};
    int WT[15] = {0};
    int gantt_time[50] = {0};
    int gantt_time_idx = 0;
    int ganttbrf_time[20] = {0};
    int ganttbrf_time_idx = 0;

    int Process_Gantt[100] = {0}; // array for storing sequence of processes in execution - gantt array
    for (int i = 0; i < 100; i++)
    {
        Process_Gantt[i] = -1;
    }

    int prc_exe_AT = AT[0];
    int TimeNow = AT[0];
    gantt_time[gantt_time_idx++]=TimeNow;
    int count = 0; // no. of iterations or no. of blocks in gantt array

    queue<int> q1; //system processes queue
    queue<int> q2; //interactive processes queue
    queue<int> q3;
    int TQ = 2;
    int completed = 0;
    int prev_time = 0;

    for (int i = 0; i < np; i++)
    { // store AT
        if (cat_prio[AT[i]] == 1)
            q3.push(AT[i]);
    }

    if (cat_prio[TimeNow] == 3)
        q1.push(TimeNow);
    if (cat_prio[TimeNow] == 2)
        q2.push(TimeNow);
   

    while (completed < np)
    {
       
        while (!q1.empty()) // high_cat is not empty
        {
            
            prc_exe_AT = q1.front();
            q1.pop();
            prev_time = TimeNow;
            if (BT_temp[prc_exe_AT] > TQ)
            {
                TimeNow += TQ;
                gantt_time[gantt_time_idx++]=TimeNow;
                BT_temp[prc_exe_AT] -= TQ;
                cout <<"System process with pid : "<<pid[prc_exe_AT] << " is executed for "<<TQ<<" seconds"<<"\n";
                Process_Gantt[count++] = pid[prc_exe_AT];
                cout << "Time now is  : " << TimeNow << "\n\n";
            }
            else
            {
                TimeNow += BT_temp[prc_exe_AT];
                gantt_time[gantt_time_idx++]=TimeNow;
                cout <<"System process with pid : "<<pid[prc_exe_AT] << " is executed for "<<BT_temp[prc_exe_AT]<<" seconds"<<"\n";
                BT_temp[prc_exe_AT] = 0;
                Process_Gantt[count++] = pid[prc_exe_AT];
                CT[pid[prc_exe_AT]] = TimeNow;
                completed++;
              //  cout <<"System process with pid : "<<pid[prc_exe_AT] << " is executed for "<<BT_temp[prc_exe_AT]<<" seconds"<<"\n";
                cout << "Time now is  : " << TimeNow << "\n";
                cout << "\nSystem Process of pid = " << pid[prc_exe_AT] << " is completed at " << TimeNow << "\n\n";
            }
            for (int i = prev_time + 1; i <= TimeNow; i++)
            {
                if (cat_prio[i] == 3)
                {
                    q1.push(i);
                }
                if (cat_prio[i] == 2)
                {
                    q2.push(i);
                }
            }
            if (BT_temp[prc_exe_AT] != 0)
            {
                q1.push(prc_exe_AT);
            }
        }


        while (!q2.empty() && q1.empty())
        {
            prc_exe_AT = q2.front();
            q2.pop();
            prev_time = TimeNow;
            if (BT_temp[prc_exe_AT] > TQ)
            {

                TimeNow += TQ;
                BT_temp[prc_exe_AT] -= TQ;
                cout <<"Interactive process with pid : "<<pid[prc_exe_AT] << " is executed for "<<TQ<<" seconds"<<"\n";
                gantt_time[gantt_time_idx++]=TimeNow;
                Process_Gantt[count++] = pid[prc_exe_AT];
                cout << "Time now is  : " << TimeNow << "\n\n";
            }

            else
            {
                TimeNow += BT_temp[prc_exe_AT];    
                cout <<"Interactive process with pid : "<<pid[prc_exe_AT] << " is executed for "<<BT_temp[prc_exe_AT]<<" seconds"<<"\n";
                BT_temp[prc_exe_AT] = 0;
                Process_Gantt[count++] = pid[prc_exe_AT];
                gantt_time[gantt_time_idx++]=TimeNow;
                CT[pid[prc_exe_AT]] = TimeNow;
                completed++;
                //cout <<"Interactive process with pid : "<<pid[prc_exe_AT] << " is executed for "<<BT_temp[prc_exe_AT]<<" seconds"<<"\n";
                cout << "Time now is  : " << TimeNow << "\n";
                cout << "\nInteractive Process of pid = " << pid[prc_exe_AT] << " is completed at " << TimeNow << "\n\n";        
            }
            
            for (int i = prev_time + 1; i <= TimeNow; i++)
            {
               
                if (cat_prio[i] == 3)
                {
                    q1.push(i);
         
                }
                if (cat_prio[i] == 2)
                {
                    q2.push(i);
            
                }
            }
            if (BT_temp[prc_exe_AT] != 0)
            {
                q2.push(prc_exe_AT);
            }
        }

        if (q1.empty() && q2.empty() && !q3.empty())
        {
           
            prc_exe_AT = q3.front();
            q3.pop();
            TimeNow += BT_temp[prc_exe_AT];
            BT_temp[prc_exe_AT] = 0;
            Process_Gantt[count++] = pid[prc_exe_AT];
            gantt_time[gantt_time_idx++]=TimeNow;
            CT[pid[prc_exe_AT]] = TimeNow;
            completed++;
            cout << "Process of pid = " << pid[prc_exe_AT] << " is completed at " << TimeNow << "\n\n";
        }
        if (q1.empty() && q2.empty() && q3.empty() && completed < np)
        {
            while (BT_temp[TimeNow] <= 0 && TimeNow < AT[np - 1])
            {
                TimeNow++;
            }
        
            // now Timenow is new Prc AT
            if (cat_prio[TimeNow] == 3)
                q1.push(TimeNow);
            if (cat_prio[TimeNow] == 2)
                q2.push(TimeNow);       
        }
    }
    
    cout << "Printing CT array :         ";
    print(CT, np);

    cout << "\n Showing gantt Chart for each second: \n";
    for (int i = 0; i < 138; i++)
        cout << "-";
    cout << endl;
    printpr(Process_Gantt);
    for (int i = 0; i < 138; i++)
        cout << "-";
    cout << endl;

    for (int i = 0; i < gantt_time_idx; i++)
    {
        if ((gantt_time[i] / 10) == 0)
            cout << gantt_time[i] << "  ";
        if ((gantt_time[i] / 10) >= 1)
            cout << gantt_time[i] << " ";
    }
    cout << endl
         << endl
         << endl;

    for (int i = 0; i < gantt_time_idx; i++)
    {
        if (Process_Gantt[i] != Process_Gantt[i - 1])
        {
            ganttbrf_time[ganttbrf_time_idx++] = gantt_time[i];
        }
    }

    cout << "\n Showing gantt Chart : \n";
    for (int i = 0; i < 138; i++)
        cout << "-";
    cout << endl;
    printprbreif(Process_Gantt);
    for (int i = 0; i < 138; i++)
        cout << "-";
    cout << endl;
    cout << "Time: ";
    for (int i = 0; i < ganttbrf_time_idx; i++)
    {
        if ((ganttbrf_time[i] / 10) == 0)
            cout << ganttbrf_time[i] << "     ";
        if ((ganttbrf_time[i] / 10) >= 1)
            cout << ganttbrf_time[i] << "    ";
    }
    cout << endl
         << endl
         << endl;

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
    for (int i = 0; i < np; i++)
    {
        cout << i << "   ";
    }

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

    return 0;
}