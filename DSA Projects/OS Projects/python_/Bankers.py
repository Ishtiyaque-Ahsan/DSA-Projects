# Function to check if a process is already solved (executed)
def solved(ans, process, count):
    for i in range(count):
        if ans[i] == process:
            return True
    return False

def main():
    print("\n IMPLEMENTING BANKERS ALGORITHM \n")

    # Number of processes and resources
    p, r = 5, 3

    # Allocation Matrix - Resources currently allocated to each process
    allocated = [
        [0, 1, 0],  # P0
        [2, 0, 0],  # P1
        [3, 0, 2],  # P2
        [2, 1, 1],  # P3
        [0, 0, 2]   # P4
    ]

    # Maximum Matrix - Total instances of resources needed by each process
    total = [
        [7, 5, 3],  # P0
        [3, 2, 2],  # P1
        [9, 0, 2],  # P2
        [2, 2, 2],  # P3
        [4, 3, 3]   # P4
    ]

    # Available resources (initially free instances)
    available = [3, 3, 2]

    # Calculate Need Matrix (Total - Allocated)
    needed = [[total[i][j] - allocated[i][j] for j in range(r)] for i in range(p)]

    # Printing allocated, total, and needed resources
    print("\nProcess   Resources-Allocated   Resources-Max   Resources-Needed")
    print("         R1  R2  R3           R1  R2  R3      R1  R2  R3")
    for i in range(p):
        print(f"  P{i}      ", end="")
        for j in range(r):
            print(f"{allocated[i][j]:<3}", end="  ")
        print("   ", end="")
        for j in range(r):
            print(f"{total[i][j]:<3}", end="  ")
        print("   ", end="")
        for j in range(r):
            print(f"{needed[i][j]:<3}", end="  ")
        print()

    # Checking if the system is in a deadlock state
    deadlock = True
    for i in range(p):
        for j in range(r):
            if needed[i][j] > available[j]:  # If any needed resource is unavailable, move to the next process
                break
            if j == r - 1:  # If all needed resources for a process are available
                deadlock = False
                print(f"Deadlock can't exist as process P{i} can get its required resources.")

    if deadlock:
        print("\nSystem is in Deadlock!\n")
        return

    print("\nSystem is not in Deadlock\n")

    # Implementing Banker's Algorithm to find a safe sequence
    ans = [-1] * p  # Stores the safe sequence of process execution
    count = 0  # Index in ans[]
    process = 0  # The current process to be checked for execution

    while count < p:  # Loop until all processes are executed
        if not solved(ans, process, count):  # If the process is not yet executed
            rc = 0  # Resource count (number of resources that can be allocated)
            for j in range(r):
                if needed[process][j] > available[j]:  # If required resources are not available, break
                    break
                rc += 1
            
            if rc == r:  # If all required resources are available for this process
                ans[count] = process
                count += 1
                print(f"P{process} is executed. Availability status of resources:")
                
                # Free its resources
                for j in range(r):
                    available[j] += allocated[process][j]
                    print(f"{available[j]}", end="  ")
                print("\n")
                process = 0  # Restart checking from the first process
            else:
                process += 1  # Move to the next process
        else:
            process += 1  # Move to the next process

    # Printing the Safe Sequence
    print("\nSafe sequence of process execution:")
    for i in range(count):
        print(f"P{ans[i]}", end=" -> " if i < count - 1 else "\n")

if __name__ == "__main__":
    main()
