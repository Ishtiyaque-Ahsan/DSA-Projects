#include <iostream>
#include <unistd.h>
#include<semaphore.h>
#include <fcntl.h>
#include <sys/wait.h>
using namespace std;

// Global semaphore to control access to chopsticks
sem_t* globalSemaphore;

int main() {
    char* semaphoreNames[5] = {"chopstick01", "chopstick11", "chopstick21", "chopstick31", "chopstick41"};
    sem_t* chopsticks[5];

    // Create a global semaphore
    globalSemaphore = sem_open("/globalSemaphore", O_CREAT | O_EXCL, 0666, 5);
    if (globalSemaphore == SEM_FAILED) {
        cout << "NOT ABLE TO CREATE THE GLOBAL SEMAPHORE\n";
        return 1;
    }

    for (int i = 0; i < 5; ++i) {
        chopsticks[i] = sem_open(semaphoreNames[i], O_CREAT | O_EXCL, 0666, 1);
        if (chopsticks[i] == SEM_FAILED) {
            cout << "NOT ABLE TO CREATE " << i << " th SEMAPHORE\n";
            return 1;
        }
    }

    for (int i = 0; i < 5; ++i) {
        pid_t p = fork();
        if (p == -1) {
            cout << "Not able to create child process\n";
            return 2;
        }
        if (p == 0) {
            int t = 2;
            while (t--) {
                cout << "philosopher " << i << " is Thinking....\n";
                usleep(1000000);
                cout << "philosopher " << i << " is Hungry....\n";

                // Philosopher waits for access to globalSemaphore
                sem_wait(globalSemaphore);

                // Philosopher picks up both chopsticks
                sem_wait(chopsticks[i]);
                sem_wait(chopsticks[(i + 1) % 5]);

                cout << "philosopher" << i << " is Eating....\n";
                usleep(1000000);

                // Philosopher releases both chopsticks
                sem_post(chopsticks[(i + 1) % 5]);
                sem_post(chopsticks[i]);

                // Philosopher releases globalSemaphore
                sem_post(globalSemaphore);
            }
            return 0;
        }
    }

    for (int i = 0; i < 5; ++i) {
        wait(NULL);
    }

    // Cleanup (closing and unlinking semaphores)
    for (int i = 0; i < 5; ++i) {
        if (sem_close(chopsticks[i]) == -1) {
            cout << "not properly closed\n";
        }
        if (sem_unlink(semaphoreNames[i]) == -1) {
            cout << "not properly unlinked\n";
        }
    }

    // Close and unlink the global semaphore
    if (sem_close(globalSemaphore) == -1) {
        cout << "not properly closed\n";
    }
    if (sem_unlink("/globalSemaphore") == -1) {
        cout << "not properly unlinked\n";
    }

    return 0;
}
// yu