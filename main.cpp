#include <string>
#include <vector>
#include <iostream>
#include <ctime>

#include "GenerateTest.cpp"
#include "CoreConstants.h"
#include "FindHalmithonPath.cpp"

int main() {
    if (NeedToGenerateDataSet) {
        GenerateDataSet();
    }
    MakeRunningDataSet();
    for (int b = 1; b <= 100; b++) {
        beat = b;
        numberOfAborted = 0;
        int cnt = 0;
        double sumtime = 0;
        for (auto t : RunningDataSet) { //Runs t-th data set
            double st = clock();
            FindHalmithonPath(t);
            double end = clock();
            sumtime += end - st;
            //std::cout << "Pass " << ++cnt << "\n";
        }
        printf("%d %0.13lf %d\n", b, sumtime / 1000, numberOfAborted);
    }
}
