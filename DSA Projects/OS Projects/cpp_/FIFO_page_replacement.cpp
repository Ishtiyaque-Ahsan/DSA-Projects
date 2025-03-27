#include <iostream>
using namespace std;

int main()
{
    int incomingStream[] = {1,2,3,4,2,1,5,6,2,1,2,3,7,6,3,2,1,2,3,6};//{7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
 //{7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1};
    int pageFaults = 0;
    int frames = 3;
    int m, n, s, pages;

    pages = sizeof(incomingStream)/sizeof(incomingStream[0]);

    printf("Incoming \t F1 \t F2 \t F3");
    int temp[frames];
    for(m = 0; m < frames; m++)
    {
        temp[m] = -1;
    }

    for(m = 0; m < pages; m++)
    {
        s = 0;  //make it 1 when pagehit

        for(n = 0; n < frames; n++)
        {
            if(incomingStream[m] == temp[n])
            {
                s++;
                pageFaults--;
            }
        }
        pageFaults++;
        
        if((pageFaults <= frames) && (s == 0))
        {
            temp[m] = incomingStream[m];
        }
        else if(s == 0)
        {
            temp[(pageFaults - 1) % frames] = incomingStream[m];
        }
      
        cout << "\n";
        cout << incomingStream[m] << "\t";
        for(n = 0; n < frames; n++)
        {
            if(temp[n] != -1)
                cout << temp[n] << "  \t";
            else
                cout << "- \t";
        }
    }

    cout << "\n\nTotal Page Faults:\t" << pageFaults;
    cout << "\nTotal Hits :\t" << pages - pageFaults;
    return 0;
}



//     int ref[n] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
