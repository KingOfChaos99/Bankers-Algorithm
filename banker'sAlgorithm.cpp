#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char** argv) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input-file>\n";
        return 1;
    }

    ifstream fin(argv[1]);
    if (!fin) {
        cerr << "Error: cannot open input file " << argv[1] << "\n";
        return 1;
    }

    int nProc, nRes;
    fin >> nProc >> nRes;
    if (!fin) {
        cerr << "Invalid input format need both nProc and nRes\n";
        return 1;
    }

    vector<int> total(nRes);
    for (int j = 0; j < nRes; ++j) fin >> total[j];

    vector<vector<int>> alloc(nProc, vector<int>(nRes));
    vector<vector<int>> maxm(nProc, vector<int>(nRes));

    // Read Allocation matrix
    for (int i = 0; i < nProc; ++i)
        for (int j = 0; j < nRes; ++j)
            fin >> alloc[i][j];

    // Read Max matrix
    for (int i = 0; i < nProc; ++i)
        for (int j = 0; j < nRes; ++j)
            fin >> maxm[i][j];

    // compute Available = total - sum(alloc)
    vector<int> available(nRes, 0);
    for (int j = 0; j < nRes; ++j) {
        int s = 0;
        for (int i = 0; i < nProc; ++i) s += alloc[i][j];
        available[j] = total[j] - s;
    }

    // compute Need = Max - Allocation
    vector<vector<int>> need(nProc, vector<int>(nRes));
    for (int i = 0; i < nProc; ++i)
        for (int j = 0; j < nRes; ++j)
            need[i][j] = maxm[i][j] - alloc[i][j];

    cout << "--- Running safety algorithm ---\n";

    vector<bool> finished(nProc, false);
    vector<int> safeSeq;
    bool progress = true;

    while ((int)safeSeq.size() < nProc && progress) {
        progress = false;
        for (int i = 0; i < nProc; ++i) {
            if (finished[i]) continue;

            bool canFinish = true;
            for (int j = 0; j < nRes; ++j)
                if (need[i][j] > available[j]) { canFinish = false; break; }

            if (canFinish) {
                finished[i] = true;
                safeSeq.push_back(i);

                // release resources
                for (int j = 0; j < nRes; ++j)
                    available[j] += alloc[i][j];

                progress = true;
            }
        }
    }

    if ((int)safeSeq.size() == nProc) {
        cout << "System is in a SAFE state.\nSafe sequence: ";
        for (size_t k = 0; k < safeSeq.size(); ++k) {
            cout << "P" << safeSeq[k];
            if (k + 1 < safeSeq.size()) cout << " -> ";
        }
        cout << "\n";
    } else {
        cout << "System is NOT in a safe state.\n";
    }

    return 0;
}
