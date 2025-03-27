#include <iostream>
using namespace std;
bool solved(int ans[], int process, int count)
{
    for (int i = 0; i < count; i++)
    {
        if (ans[i] == process)
            return true;
    }
    return false;
}
int main()
{
    /* code */
    cout<<"\n IMPLEMENTING BANKERS ALGORITHM \n";
    int p = 5, r = 3;
    int allocated[p][r] = {{0, 1, 0},  // P0 // Allocation Matrix
                           {2, 0, 0},  // P1
                           {3, 0, 2},  // P2
                           {2, 1, 1},  // P3
                           {0, 0, 2}}; // P4

    int total[p][r] = {{7, 5, 3},  // P0 // Total instances of the resources to be used by processse Matrix
                       {3, 2, 2},  // P1
                       {9, 0, 2},  // P2
                       {2, 2, 2},  // P3
                       {4, 3, 3}}; // P4

    int available[r] = {3, 3, 2};  //resource instances available free now
    int needed[p][r];  //Extra instances of the resources to be needed by processse
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < r; j++)
            needed[i][j] = total[i][j] - allocated[i][j];
    }

    // printing resources allocted , resource-totalUsed and resources-needed for processes
    cout<<"Process  Resources-Allocated  Resources-totalUsed   Resources-Needed  \n";
    cout<<"           R1   R2   R3           R1   R2    R3         R1   R2    R3   \n";
    for (int i = 0; i < p; i++)
    {
        cout<<"   "<<i<<"       ";
        for (int j = 0; j < r; j++){
            cout<<allocated[i][j]<<"    ";       
         } 
        cout<<"        ";    
        for (int j = 0; j < r; j++){
            cout<<total[i][j]<<"    ";       
        }
        cout<<"        ";  
        for (int j = 0; j < r; j++){
            cout<<needed[i][j]<<"    ";       
        }
        cout<<"        \n";  
    }           
    
    //checking if the system is in deadlock or not
    bool deadlock = true;
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < r; j++){
            if(needed[i][j] > available[j]){
                break;
            }
            if(j == r-1){
                deadlock = false;
                cout<<"Deadlock can't exist as this process P"<<i<<" can get its required recources \n";
            }
        } 
    }      
    if(deadlock == true){
        cout<<"System is in Deadlock\n";
        return 0;
    }
    if(deadlock == false){
        cout<<"\nSystem is not in Deadlock\n\n";
    }

    // will proceed to resource allocation if system is not in Deadlock

    int ans[p];  //contains the processes in order of their execution depending upon resource allocations
    int count = 0;   // index count in ans
    int process = 0; // process whose  availablity and need is compared 
    //and based on which it will be decide to skip this process now or give the needed resources
    

    while (count < p)   //untill all processes are executed
    {
        
        if (!solved(ans, process, count))
        {
            // process is not solved yet
            int rc = 0; // recourse count = no. of complete resources(all req instances) which can be given to this process now
            for (int j = 0; j < r; j++)
            {
                if (needed[process][j] > available[j])
                {
                    break;
                }
                rc++;
            }
            if (rc == r)
            { // this process can be given resources as all its req are available
                ans[count++] = process;
                cout<<"P"<<process<<" is executed \nAvailability Status of Resources are : ";
                // free its resources
                for (int j = 0; j < r; j++)
                {
                    available[j] += allocated[process][j];
                    cout<<available[j]<<" ";
                }
                cout<<endl;
                // now go for succeededing prcersses
                process = 0;
            }
            else
            { /// this process cannot be given resources now
                process++;
            }
        }
        else{
            process++;
        }
    }
    cout<<"\nPrinting safe sequence of process to be allocated the resources they needed \n\n";
    for (int i = 0; i < count; i++)
    {
        cout<<"P"<<ans[i];
        if(i < count-1){
            cout<<" -> ";
        }
    }
    
    return 0;
}
