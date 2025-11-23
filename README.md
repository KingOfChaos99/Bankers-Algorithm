# Bankers-Algorithm

The program reads process allocation data from the input file, computes the needs of each remaining process, and determines if the system is in a safe state. If the system is safe, the program outputs a safe sequence in which all processes may complete without causing a deadlock.
The system includes:
5 processes: P0–P4


3 resource types: A, B, C


Total instances: A=10, B=5, C=7



Banker’s Algorithm — Explanation
Banker’s Algorithm is used by operating systems to ensure that resource allocation to processes does not lead to deadlock.
The algorithm uses four vectors:
Allocation[i][j]
Currently allocated resources of type j to process i
Max[i][j]
Maximum resources process i may request
Need[i][j] = Max – Allocation
Remaining resources required by process i
Available[j]
Remaining free resources of type j

Safety Check
The safety algorithm works as follows:
Look for a process whose Need <= Available.

Pretend to “run” that process by adding its Allocation back to Available.

Mark the process as done.

Repeat until either:

All processes finish → safe state

No progress possible → unsafe state

If all processes can finish, the algorithm outputs the safe sequence.

Input File Format
The program reads a .txt input file structured as follows:
<number_of_processes> <number_of_resources>
<total_resource_vector>
<Allocation matrix (P0 to Pn)>
<Max matrix (P0 to Pn)>

Example (input.txt)
5 3
10 5 7
0 1 0
2 0 0
3 0 2
2 2 1
0 0 2
7 5 3
3 3 2
9 0 2
2 2 2
4 3 3

Compilation Instructions

Compile (in Linux/Unix):
g++ -std=c++17 banker.cpp -o banker

Run (in Linux/Unix):
./banker input.txt


Program Output Example
When run using the snapshot (input above), the program produces output like this:
--- Running safety algorithm ---
System is in a SAFE state.
Safe sequence: P3 -> P4 -> P1 -> P2 -> P0
