#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
#include <climits>

using namespace std;

void sortSegment(vector<int>& arr) {
    sort(arr.begin(), arr.end());
}

int createInitialRuns(const char* inputFile, int memSize, const string& prefix) {
    ifstream in(inputFile);
    vector<int> buffer;
    buffer.reserve(memSize);
    int runCount = 0;
    int num;
    
    while (in >> num) {
        buffer.push_back(num);
        
        if (buffer.size() == memSize) {
            sortSegment(buffer);
            ofstream out(prefix + to_string(runCount) + ".dat");
            for (int val : buffer) out << val << " ";
            out.close();
            buffer.clear();
            runCount++;
        }
    }
    
    if (!buffer.empty()) {
        sortSegment(buffer);
        ofstream out(prefix + to_string(runCount) + ".dat");
        for (int val : buffer) out << val << " ";
        out.close();
        runCount++;
    }
    
    in.close();
    return runCount;
}

void mergeTwoFiles(const string& file1, const string& file2, const string& outputFile) {
    ifstream f1(file1), f2(file2);
    ofstream out(outputFile);
    
    int a, b;
    bool has1 = false, has2 = false;
    
    if (f1 >> a) has1 = true;
    if (f2 >> b) has2 = true;
    
    while (has1 || has2) {
        if (!has1) {
            out << b << " ";
            if (f2 >> b) has2 = true;
            else has2 = false;
        } else if (!has2) {
            out << a << " ";
            if (f1 >> a) has1 = true;
            else has1 = false;
        } else if (a <= b) {
            out << a << " ";
            if (f1 >> a) has1 = true;
            else has1 = false;
        } else {
            out << b << " ";
            if (f2 >> b) has2 = true;
            else has2 = false;
        }
    }
    
    f1.close(); f2.close(); out.close();
}

void simpleMergeSort(const char* inputFile, const char* outputFile, int memSize) {
    int runCount = createInitialRuns(inputFile, memSize, "simple_");
    
    int level = 0;
    while (runCount > 1) {
        int newRunCount = 0;
        
        for (int i = 0; i < runCount; i += 2) {
            string f1 = "simple_" + to_string(i) + ".dat";
            
            if (i + 1 < runCount) {
                string f2 = "simple_" + to_string(i + 1) + ".dat";
                string outFile = "simple_merge_" + to_string(level) + "_" + to_string(newRunCount) + ".dat";
                mergeTwoFiles(f1, f2, outFile);
                remove(f1.c_str());
                remove(f2.c_str());
            } else {
                string outFile = "simple_merge_" + to_string(level) + "_" + to_string(newRunCount) + ".dat";
                rename(f1.c_str(), outFile.c_str());
            }
            newRunCount++;
        }
        
        for (int i = 0; i < newRunCount; i++) {
            string oldName = "simple_merge_" + to_string(level) + "_" + to_string(i) + ".dat";
            string newName = "simple_" + to_string(i) + ".dat";
            rename(oldName.c_str(), newName.c_str());
        }
        
        runCount = newRunCount;
        level++;
    }
    
    if (runCount == 1) {
        ifstream in("simple_0.dat");
        ofstream out(outputFile);
        int val;
        while (in >> val) out << val << " ";
        in.close(); out.close();
        remove("simple_0.dat");
    }
}

void balancedTwoPhaseMerge(const char* inputFile, const char* outputFile, int runSize) {
    int runCount = createInitialRuns(inputFile, runSize, "balance_");
    
    for (int i = 0; i < runCount; i++) {
        string oldName = "balance_" + to_string(i) + ".dat";
        string newName = (i % 2 == 0) ? "A_" + to_string(i/2) + ".dat" : "B_" + to_string(i/2) + ".dat";
        rename(oldName.c_str(), newName.c_str());
    }
    
    int aCount = (runCount + 1) / 2;
    int bCount = runCount / 2;
    
    while (aCount + bCount > 1) {
        int newACount = 0, newBCount = 0;
        
        for (int i = 0; i < max(aCount, bCount); i++) {
            string fileA = (i < aCount) ? "A_" + to_string(i) + ".dat" : "";
            string fileB = (i < bCount) ? "B_" + to_string(i) + ".dat" : "";
            
            if (!fileA.empty() && !fileB.empty()) {
                string outFile = "A_new_" + to_string(newACount) + ".dat";
                mergeTwoFiles(fileA, fileB, outFile);
                remove(fileA.c_str());
                remove(fileB.c_str());
                newACount++;
                
                i++;
                if (i < aCount || i < bCount) {
                    string nextA = (i < aCount) ? "A_" + to_string(i) + ".dat" : "";
                    string nextB = (i < bCount) ? "B_" + to_string(i) + ".dat" : "";
                    
                    if (!nextA.empty() && !nextB.empty()) {
                        outFile = "B_new_" + to_string(newBCount) + ".dat";
                        mergeTwoFiles(nextA, nextB, outFile);
                        if (!nextA.empty()) remove(nextA.c_str());
                        if (!nextB.empty()) remove(nextB.c_str());
                        newBCount++;
                    } else if (!nextA.empty()) {
                        rename(nextA.c_str(), ("B_new_" + to_string(newBCount) + ".dat").c_str());
                        newBCount++;
                    } else if (!nextB.empty()) {
                        rename(nextB.c_str(), ("B_new_" + to_string(newBCount) + ".dat").c_str());
                        newBCount++;
                    }
                }
            } else if (!fileA.empty()) {
                rename(fileA.c_str(), (newBCount < newACount ? "B_new_" + to_string(newBCount) : "A_new_" + to_string(newACount)).c_str());
                if (newBCount < newACount) newBCount++;
                else newACount++;
            } else if (!fileB.empty()) {
                rename(fileB.c_str(), (newBCount < newACount ? "B_new_" + to_string(newBCount) : "A_new_" + to_string(newACount)).c_str());
                if (newBCount < newACount) newBCount++;
                else newACount++;
            }
        }
        
        for (int i = 0; i < newACount; i++) {
            rename(("A_new_" + to_string(i) + ".dat").c_str(), ("A_" + to_string(i) + ".dat").c_str());
        }
        for (int i = 0; i < newBCount; i++) {
            rename(("B_new_" + to_string(i) + ".dat").c_str(), ("B_" + to_string(i) + ".dat").c_str());
        }
        
        aCount = newACount;
        bCount = newBCount;
    }
    
    string resultFile = (aCount == 1) ? "A_0.dat" : "B_0.dat";
    ifstream in(resultFile);
    ofstream out(outputFile);
    int val;
    while (in >> val) out << val << " ";
    in.close(); out.close();
    remove(resultFile.c_str());
}

void multiwayMerge(const char* inputFile, const char* outputFile, int runSize, int ways) {
    int runCount = createInitialRuns(inputFile, runSize, "multi_");
    
    while (runCount > 1) {
        int newRunCount = 0;
        
        for (int i = 0; i < runCount; i += ways) {
            vector<ifstream> readers;
            vector<int> currentVals;
            vector<bool> hasVals;
            
            for (int j = 0; j < ways && i + j < runCount; j++) {
                string fname = "multi_" + to_string(i + j) + ".dat";
                ifstream f(fname);
                readers.push_back(move(f));
                int val;
                if (readers[j] >> val) {
                    currentVals.push_back(val);
                    hasVals.push_back(true);
                } else {
                    currentVals.push_back(0);
                    hasVals.push_back(false);
                }
            }
            
            string outFile = "multi_merged_" + to_string(newRunCount) + ".dat";
            ofstream out(outFile);
            
            int activeCount = readers.size();
            while (activeCount > 0) {
                int minVal = INT_MAX;
                int minIdx = -1;
                
                for (size_t j = 0; j < readers.size(); j++) {
                    if (hasVals[j] && currentVals[j] < minVal) {
                        minVal = currentVals[j];
                        minIdx = j;
                    }
                }
                
                if (minIdx != -1) {
                    out << minVal << " ";
                    int newVal;
                    if (readers[minIdx] >> newVal) {
                        currentVals[minIdx] = newVal;
                    } else {
                        hasVals[minIdx] = false;
                        activeCount--;
                    }
                }
            }
            out.close();
            
            for (size_t j = 0; j < readers.size(); j++) {
                readers[j].close();
                string fname = "multi_" + to_string(i + j) + ".dat";
                remove(fname.c_str());
            }
            
            newRunCount++;
        }
        
        for (int i = 0; i < newRunCount; i++) {
            string oldName = "multi_merged_" + to_string(i) + ".dat";
            string newName = "multi_" + to_string(i) + ".dat";
            rename(oldName.c_str(), newName.c_str());
        }
        
        runCount = newRunCount;
    }
    
    ifstream in("multi_0.dat");
    ofstream out(outputFile);
    int val;
    while (in >> val) out << val << " ";
    in.close(); out.close();
    remove("multi_0.dat");
}

int main() {
    ofstream test("test.txt");
    int original[] = {64, 25, 12, 22, 11, 90, 45, 33, 78, 5, 88, 41, 29, 55, 17, 99, 3, 71, 60, 8};
    for (int i = 0; i < 20; i++) {
        test << original[i];
        if (i < 19) test << " ";
    }
    test.close();
    
    cout << "Original array: ";
    for (int i = 0; i < 20; i++) cout << original[i] << " ";
    cout << endl << endl;
    
    simpleMergeSort("test.txt", "output_simple.txt", 5);
    balancedTwoPhaseMerge("test.txt", "output_balanced.txt", 5);
    multiwayMerge("test.txt", "output_multi.txt", 5, 3);
    
    ifstream sres("output_simple.txt");
    cout << "Simple merge:        ";
    int v;
    for (int i = 0; i < 20 && sres >> v; i++) cout << v << " ";
    cout << endl;
    sres.close();
    
    ifstream bres("output_balanced.txt");
    cout << "Balanced two-phase:  ";
    for (int i = 0; i < 20 && bres >> v; i++) cout << v << " ";
    cout << endl;
    bres.close();
    
    ifstream mres("output_multi.txt");
    cout << "Multiway (3-phase):  ";
    for (int i = 0; i < 20 && mres >> v; i++) cout << v << " ";
    cout << endl;
    mres.close();
    
    return 0;
}