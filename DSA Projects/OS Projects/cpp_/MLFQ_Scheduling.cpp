/*

MLFQ CPU Scheduling is implemented here
First Queue Proceses -> Round Robin
Second Queue Proceses -> Round Robin
Third Queue Proceses -> Round Robin
Fourth Queue Proceses -> FCFS
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
    // AT[0] = 1;
    // AT[1] = 3;
    // AT[2] = 4;
    // AT[3] = 7;
    // AT[4] = 8;
    // AT[5] = 13;
    // AT[6] = 15;
    // AT[7] = 28;

    // BT[1] = 6;
    // BT[3] = 2;
    // BT[4] = 3;
    // BT[7] = 4;
    // BT[8] = 5;
    // BT[13] = 2;
    // BT[15] = 3;
    // BT[28] = 6;

    // cat_prio[1] = 3; // second priority process
    // cat_prio[3] = 2; // third priority process
    // cat_prio[4] = 4; // first priority process
    // cat_prio[7] = 1; // fourth priority process
    // cat_prio[8] = 1;
    // cat_prio[13] = 2;
    // cat_prio[15] = 4;
    // cat_prio[28] = 3;

    sort(AT, np);
    // giving sequential pid to processes based on AT as pid =0,1,2,3,...
    for (int i = 0; i < np; i++)
    {
        pid[AT[i]] = i;
    }
    cout<<"Cat_prio is category priority which is higher for higher priority queues\n";
    cout<<"cat_prio value is :\n 4 for first priority process ,\n 3 for second priority process ,\n 2 for third priority process ,\n 1 for fourth priority process\n ";
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
    gantt_time[gantt_time_idx++] = TimeNow;
    int count = 0; // no. of iterations or no. of blocks in gantt array

    queue<int> first_q;
    queue<int> second_q;
    queue<int> third_q;
    queue<int> fourth_q;
    int TQ = 2;
    int TQ3 = 3;
    int completed = 0;
    int prev_time = 0;

    if (cat_prio[TimeNow] == 4)
        first_q.push(TimeNow);
    if (cat_prio[TimeNow] == 3)
        second_q.push(TimeNow);
    if (cat_prio[TimeNow] == 2)
        third_q.push(TimeNow);
    if (cat_prio[TimeNow] == 1)
        fourth_q.push(TimeNow);

    while (completed < np)
    {
        while (!first_q.empty()) // high_cat is not empty
        {
            
            prc_exe_AT = first_q.front();
            first_q.pop();
            prev_time = TimeNow;
            if (BT_temp[prc_exe_AT] > TQ)
            {
                TimeNow += TQ;
                gantt_time[gantt_time_idx++] = TimeNow;
                BT_temp[prc_exe_AT] -= TQ;
                cout << "First category process with pid : " << pid[prc_exe_AT] << " is executed for " << TQ << " seconds"
                     << "\n";
                Process_Gantt[count++] = pid[prc_exe_AT];
                cout << "Time now is  : " << TimeNow << "\n\n";
                cat_prio[prc_exe_AT]--;
            }
            else
            {
                TimeNow += BT_temp[prc_exe_AT];
                gantt_time[gantt_time_idx++] = TimeNow;
                cout << "First category process with pid : " << pid[prc_exe_AT] << " is executed for " << BT_temp[prc_exe_AT] << " seconds"
                     << "\n";
                BT_temp[prc_exe_AT] = 0;
                Process_Gantt[count++] = pid[prc_exe_AT];
                CT[pid[prc_exe_AT]] = TimeNow;
                completed++;
                //  cout <<"First category process with pid : "<<pid[prc_exe_AT] << " is executed for "<<BT_temp[prc_exe_AT]<<" seconds"<<"\n";
                cout << "Time now is  : " << TimeNow << "\n";
                cout << "\nFirst category Process of pid = " << pid[prc_exe_AT] << " is completed at " << TimeNow << "\n\n";
            }
            for (int i = prev_time + 1; i <= TimeNow; i++)
            {
                if (cat_prio[i] == 4)
                {
                    first_q.push(i);
                   // cout<<"meanwhile pushing "<<pid[i]<<" in first queue\n";
                }
                if (cat_prio[i] == 3)
                {
                    second_q.push(i);
                   // cout<<"meanwhile pushing "<<pid[i]<<" in sec queue\n";
                }
                if (cat_prio[i] == 2)
                {
                    third_q.push(i);
                   // cout<<"meanwhile pushing "<<pid[i]<<" in third queue\n";
                }
                if (cat_prio[i] == 1)
                {
                    fourth_q.push(i);
                }
                
            }
            if (BT_temp[prc_exe_AT] != 0)
            {
                second_q.push(prc_exe_AT);
                cout<<pid[prc_exe_AT]<<" is now pushed in second queue \n";
            }
        }

        
        while (!second_q.empty() && first_q.empty())
        {
           // cout<<"In sec cat case\n";
            prc_exe_AT = second_q.front();
            second_q.pop();
            prev_time = TimeNow;
            if (BT_temp[prc_exe_AT] > TQ)
            {

                TimeNow += TQ;
                BT_temp[prc_exe_AT] -= TQ;
                cout << "Second category process with pid : " << pid[prc_exe_AT] << " is executed for " << TQ << " seconds"
                     << "\n";
                gantt_time[gantt_time_idx++] = TimeNow;
                Process_Gantt[count++] = pid[prc_exe_AT];
                cout << "Time now is  : " << TimeNow << "\n\n";
                cat_prio[prc_exe_AT]--;
            }

            else
            {
                TimeNow += BT_temp[prc_exe_AT];
                cout << "Second category process with pid : " << pid[prc_exe_AT] << " is executed for " << BT_temp[prc_exe_AT] << " seconds"
                     << "\n";
                BT_temp[prc_exe_AT] = 0;
                Process_Gantt[count++] = pid[prc_exe_AT];
                gantt_time[gantt_time_idx++] = TimeNow;
                CT[pid[prc_exe_AT]] = TimeNow;
                completed++;
                // cout <<"Interactive process with pid : "<<pid[prc_exe_AT] << " is executed for "<<BT_temp[prc_exe_AT]<<" seconds"<<"\n";
                cout << "Time now is  : " << TimeNow << "\n";
                cout << "\nSecond category Process of pid = " << pid[prc_exe_AT] << " is completed at " << TimeNow << "\n\n";
            }

            for (int i = prev_time + 1; i <= TimeNow; i++)
            {

                if (cat_prio[i] == 4)
                {
                    first_q.push(i);
                  //  cout<<"meanwhile pushing "<<pid[i]<<" in first queue\n";
                }
                if (cat_prio[i] == 3)
                {
                    second_q.push(i);
                  //  cout<<"meanwhile pushing "<<pid[i]<<" in sec queue\n";
                }
                if (cat_prio[i] == 2)
                {
                    third_q.push(i);
                  //  cout<<"meanwhile pushing "<<pid[i]<<" in third queue\n";
                }
                if (cat_prio[i] == 1)
                {
                    fourth_q.push(i);
                }
                
            }
            if (BT_temp[prc_exe_AT] != 0)
            {
                third_q.push(prc_exe_AT);
                cout<<pid[prc_exe_AT]<<" is now pushed in third queue \n";
            }
        }


        while (!third_q.empty() && second_q.empty() && first_q.empty())
        {
           // cout<<"In third cat case\n";
            prc_exe_AT = third_q.front();
            third_q.pop();
            prev_time = TimeNow;
            if (BT_temp[prc_exe_AT] > TQ)
            {

                TimeNow += TQ;
                BT_temp[prc_exe_AT] -= TQ;
                cout << "Third category process with pid : " << pid[prc_exe_AT] << " is executed for " << TQ << " seconds"
                     << "\n";
                gantt_time[gantt_time_idx++] = TimeNow;
                Process_Gantt[count++] = pid[prc_exe_AT];
                cout << "Time now is  : " << TimeNow << "\n\n";
                cat_prio[prc_exe_AT]--;
            }

            else
            {
                TimeNow += BT_temp[prc_exe_AT];
                cout << "Third category process with pid : " << pid[prc_exe_AT] << " is executed for " << BT_temp[prc_exe_AT] << " seconds"
                     << "\n";
                BT_temp[prc_exe_AT] = 0;
                Process_Gantt[count++] = pid[prc_exe_AT];
                gantt_time[gantt_time_idx++] = TimeNow;
                CT[pid[prc_exe_AT]] = TimeNow;
                completed++;
                // cout <<"Interactive process with pid : "<<pid[prc_exe_AT] << " is executed for "<<BT_temp[prc_exe_AT]<<" seconds"<<"\n";
                cout << "Time now is  : " << TimeNow << "\n";
                cout << "\nThird category Process of pid = " << pid[prc_exe_AT] << " is completed at " << TimeNow << "\n\n";
            }

            for (int i = prev_time + 1; i <= TimeNow; i++)
            {
                if (cat_prio[i] == 4)
                {
                    first_q.push(i);
                   // cout<<"meanwhile pushing "<<pid[i]<<" in first queue\n";
                }
                if (cat_prio[i] == 3)
                {
                    second_q.push(i);
                  //  cout<<"meanwhile pushing "<<pid[i]<<" in sec queue\n";
                }
                if (cat_prio[i] == 2)
                {
                    third_q.push(i);
                  //  cout<<"meanwhile pushing "<<pid[i]<<" in third queue\n";
                }
                if (cat_prio[i] == 1)
                {
                    fourth_q.push(i);
                }
                
            }
            if (BT_temp[prc_exe_AT] != 0)
            {
                fourth_q.push(prc_exe_AT);
                cout<<pid[prc_exe_AT]<<" is now pushed in fourth queue \n";
            }
        }

        if (first_q.empty() && second_q.empty() && third_q.empty() && !fourth_q.empty())
        {
           // cout<<"In fourth cat case\n";
            prev_time = TimeNow;
            prc_exe_AT = fourth_q.front();
            fourth_q.pop();
         
            TimeNow += BT_temp[prc_exe_AT];
            BT_temp[prc_exe_AT] = 0;
            Process_Gantt[count++] = pid[prc_exe_AT];
            gantt_time[gantt_time_idx++] = TimeNow;
            CT[pid[prc_exe_AT]] = TimeNow;
            completed++;
            cout << "Fourth categoryProcess of pid = " << pid[prc_exe_AT] << " is completed at " << TimeNow << "\n\n";

            for (int i = prev_time + 1; i <= TimeNow; i++)
            {
                if (cat_prio[i] == 4)
                {
                    first_q.push(i);
                    //cout<<"meanwhile pushing "<<pid[i]<<" in first queue\n";
                }
                if (cat_prio[i] == 3)
                {
                    second_q.push(i);
                    //cout<<"meanwhile pushing "<<pid[i]<<" in sec queue\n";
                }
                if (cat_prio[i] == 2)
                {
                    third_q.push(i);
                    //cout<<"meanwhile pushing "<<pid[i]<<" in third queue\n";
                }
                if (cat_prio[i] == 1)
                {
                    fourth_q.push(i);
                }
                
            }
        }
        if (first_q.empty() && second_q.empty() && third_q.empty() && fourth_q.empty() && completed < np)
        {
            cout<<"empty case \n";
            while (BT_temp[TimeNow] <= 0 && TimeNow < AT[np - 1])
            {
                TimeNow++;
            }

            // now Timenow is new Prc AT
            if (cat_prio[TimeNow] == 4)
                first_q.push(TimeNow);
            if (cat_prio[TimeNow] == 3)
                second_q.push(TimeNow);
            if (cat_prio[TimeNow] == 2)
                third_q.push(TimeNow);
            if (cat_prio[TimeNow] == 1)
                fourth_q.push(TimeNow);
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
