#pragma once
#include <random>
#include <vector>
#include <algorithm>
#include <fstream>

#include "CoreConstants.h"

using namespace std;

void GenerateTest(int NumOfTest) {
    int countOfVertices = 2 + rand() % (nMAX - 1);
    vector < int > order(countOfVertices); //Make a random path in graph
    for (int i = 0; i < countOfVertices; i++)
        order[i] = i;
    shuffle(order.begin(), order.end(), std::mt19937(std::random_device()()));
    vector < pair<int,int> > edges;
    for (int i = 0; i + 1 < countOfVertices; i++)
        edges.emplace_back(order[i], order[i + 1]);
    int countOfRestEdges = 1 + rand() % min(mMAX, countOfVertices * (countOfVertices - 1) / 2) - (countOfVertices - 1);
    int countOfEdges = countOfRestEdges + countOfVertices - 1;
    for (int _ = 0; _ < countOfRestEdges; _++) { //Add extra edges
        do {
            int u = rand() % countOfVertices;
            int v = rand() % countOfVertices;
            if (u == v)
                continue;
            bool isexist = false;
            for (auto e : edges) {
                if (e == make_pair(u, v) || e == make_pair(v, u)) {
                    isexist = true;
                    break;
                }
            }
            if (!isexist) {
                edges.emplace_back(u, v);
                break;
            }
        } while (true);
    }
    shuffle(edges.begin(), edges.end(), std::mt19937(std::random_device()()));
    {
        string FilePath = PathDataSet + to_string(NumOfTest);
        ofstream File(FilePath);
        File<<countOfVertices<<" "<<countOfEdges<<"\n";
        for (auto e : edges) {
            File<<e.first + 1<<" "<<e.second + 1<<"\n";
        }
        File.close();
    }
}

void GenerateDataSet() {
    for (int NumOfTest = 0; NumOfTest < CountOfDataSet; NumOfTest++) {
        GenerateTest(NumOfTest);
    }
}

void MakeRunningDataSet() {
    if (RunAllTests) {
        RunningDataSet.resize(CountOfDataSet);
        for (int t = 0; t < CountOfDataSet; t++)
            RunningDataSet[t] = t;
    }
}
