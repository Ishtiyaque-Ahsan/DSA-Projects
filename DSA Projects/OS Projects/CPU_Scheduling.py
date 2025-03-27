
# Taking pid , AT and BT and Priority of the processes as input
# SJf Scheduling (Non-Preemptive) is implemented here
# Priority Scheduling (Preemptive) is implemented here
# Round Robin Scheduling  is implemented here

import queue

def sort(arr):
    arr.sort()

def max_priority(prio, k, BT_temp, np):
    max_pr = -6
    pr_idx = -2
    em = 0
    for i in range(k + 1):
        if prio[i] != 0:
            em += 1
            if prio[i] > max_pr and BT_temp[i] != 0:
                max_pr = prio[i]
                pr_idx = i
    if pr_idx == -2:
        return -2 if em == np else -10
    return pr_idx

def min_burst(BT_temp, k):
    min_bt = float('inf')
    min_idx = -10
    for i in range(k + 1):
        if 0 < BT_temp[i] < min_bt:
            min_bt = BT_temp[i]
            min_idx = i
    return min_idx

def SJF_Sch(BT, AT, CT, Pr, np, pid):
    BT_temp = BT.copy()
    TimeNow = 0
    k = 0

    for i in range(np):
        process_AT = min_burst(BT_temp, k)
        if process_AT == -10:
            s = k
            while BT_temp[s] <= 0:
                s += 1
            process_AT = s
            TimeNow = s

        c = sum(1 for j in range(process_AT + 1) if BT[j] > 0) - 1
        print(f"Process executed: P{pid[process_AT]}")
        Pr[i] = pid[process_AT]
        CT[c] = TimeNow + BT_temp[process_AT]
        TimeNow = CT[c]
        k = min(49, CT[c])
        BT_temp[process_AT] = 0

def Priority_Sch(BT, AT, Priority, CT, Pr, np, pid):
    BT_temp = BT.copy()
    TimeNow = 0
    k = 0
    count = 0

    while True:
        process_AT = max_priority(Priority, k, BT_temp, np)
        if process_AT == -2:
            break

        if process_AT == -10:
            s = k
            while BT_temp[s] <= 0:
                s += 1
            process_AT = s
            TimeNow = s

        c = sum(1 for j in range(process_AT + 1) if BT[j] > 0) - 1
        print(f"Process executed: P{pid[process_AT]}")
        Pr[count] = pid[process_AT]
        count += 1
        BT_temp[process_AT] -= 1
        TimeNow += 1
        if BT_temp[process_AT] == 0:
            CT[c] = TimeNow
        k = min(49, TimeNow)

def RoundRobin_Sch(BT, AT, TQ, CT, Pr, np, pid):
    BT_temp = BT.copy()
    TimeNow = 0
    q = queue.Queue()
    e = 0
    q.put(0)
    TimeNow = AT[0]
    e += 1
    pr_idx = 0

    while not q.empty():
        pr_exe = q.get()
        Process_id = pid[AT[pr_exe]]
        Pr[pr_idx] = Process_id
        print(f"Process executed: P{Process_id}")
        process_AT = AT[pr_exe]

        if BT_temp[process_AT] >= TQ:
            TimeNow += TQ
            BT_temp[process_AT] -= TQ
        else:
            TimeNow += BT_temp[process_AT]
            BT_temp[process_AT] = 0

        while e < np and AT[e] <= TimeNow:
            q.put(e)
            e += 1

        if BT_temp[process_AT] > 0:
            q.put(pr_exe)

        if BT_temp[process_AT] == 0:
            CT[pr_exe] = TimeNow

        pr_idx += 1

        if q.empty() and e < np:
            s = TimeNow
            while BT_temp[s] <= 0:
                s += 1
            TimeNow = s
            q.put(e)
            e += 1

def main():
    np = int(input("Enter number of processes: "))
    TQ = int(input("\nEnter Time Quantum for Round Robin: "))

    AT = [0] * 15
    pid = [-1] * 50
    BT = [0] * 50
    Priority = [0] * 50

    AT[:np] = [4, 3, 8, 0, 6, 1]
    pid[4], pid[3], pid[8], pid[0], pid[6], pid[1] = 1, 2, 3, 4, 5, 6
    BT[4], BT[3], BT[8], BT[0], BT[6], BT[1] = 8, 3, 5, 6, 2, 4
    Priority[4], Priority[3], Priority[8], Priority[0], Priority[6], Priority[1] = 1, 2, 3, 4, 5, 6

    sort(AT[:np])

    print("\nProcess ID | AT | Priority | BT")
    for i in range(np):
        print(f"    {pid[AT[i]]}       {AT[i]}      {Priority[AT[i]]}        {BT[AT[i]]}")

    CT = [0] * 15
    Process_Gantt = [-1] * 100

    for z in range(3):
        if z == 0:
            print("\nApplying SJF (Non-Preemptive) Scheduling:")
            SJF_Sch(BT, AT, CT, Process_Gantt, np, pid)
        elif z == 1:
            print("\nApplying Priority (Preemptive) Scheduling:")
            Priority_Sch(BT, AT, Priority, CT, Process_Gantt, np, pid)
        else:
            print("\nApplying Round-Robin Scheduling:")
            RoundRobin_Sch(BT, AT, TQ, CT, Process_Gantt, np, pid)

        TAT = [(CT[i] - AT[i]) for i in range(np)]
        WT = [(TAT[i] - BT[AT[i]]) for i in range(np)]
        avgTAT = sum(TAT) / np
        avgWT = sum(WT) / np

        print("\nCT Array:", CT)
        print("TAT Array:", TAT)
        print("WT Array:", WT)
        print(f"Avg TAT: {avgTAT}   Avg WT: {avgWT}")
        print("\nProcesses Execution Sequence:", [p for p in Process_Gantt if p != -1])

        CT[:] = [0] * 15
        Process_Gantt[:] = [-1] * 100

if __name__ == "__main__":
    main()
