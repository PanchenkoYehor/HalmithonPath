#pragma once
#include <vector>
#include <queue>
#include <fstream>
#include "CoreConstants.h"

using namespace std;

bool is_correct(vector < vector < int > > &g, vector < int > &path) {
    for (int i = 0; i < path.size(); i++)
        for (int j = i + 1; j < path.size(); j++)
            if (path[i] == path[j])
                return false;
    for (int i = 0; i + 1 < path.size(); i++) {
        bool ex = false;
        for (auto u : g[path[i]])
            if (u == path[i + 1]) {
                ex = true;
                break;
            }
        if (!ex)
            return false;
    }
    return true;
}

double stRec;

void Rec(ofstream &out, vector < vector < int > > &g, vector < int > & used, int &last, int cnt, int may, int val, int n, int beat, int first, bool &isfind) {
    if (isfind)
        return;
    double endRec = clock();
    if ((endRec - stRec) / 1000 >= timeMAX) {
        numberOfAborted++;
        isfind = true;
        return;
    }
    if (cnt >= 50 && cnt % beat == 0 && !may) { //Check if connected
        queue < int > Q;
        vector < int > usd(n, 0);
        Q.push(last);
        usd[last] = 1;
        int c = 0;
        while (!Q.empty()) {
            c++;
            int head = Q.front();
            Q.pop();
            for (auto u : g[head]) {
                if (usd[u])
                    continue;
                usd[u] = 1;
                Q.push(u);
            }
        }
        if (c + cnt - 1 != n)
            return;
    }
    if (cnt == n) {
        vector < pair<int,int> > v(n);
        for (int i = 0; i < n; i++)
            v[i] = {used[i], i};
        sort(v.begin(), v.end());
        vector < int > path;
        for (int i = val - 1; i >= 0; i--)
            path.push_back(v[i].second);
        for (int i = val; i < n; i++)
            path.push_back(v[i].second);
        if (is_correct(g, path)) {
            for (auto i : path)
                out<<i + 1<<" ";
            out << "\n";
            out.close();
            isfind = true;
        } else {
            cout<<"Wrong path\n";
        }
        return;
    }
    bool go = false;
    for (auto u : g[last]) {
        if (used[u])
            continue;
        go = true;
        used[u] = cnt + 1;
        Rec(out, g, used, u, cnt + 1, may, val, n, beat, first, isfind);
        if (isfind)
            return;
        used[u] = 0;
    }
    if (!go && may) {
        Rec(out, g, used, first, cnt, 0, cnt, n, beat, first, isfind);
    }
}

void FindHalmithonPath(int numOfTest) {
    stRec = clock();
    string DataFileName = PathDataSet + to_string(numOfTest);
    ifstream DataFile(DataFileName);
    string OutputFileName = PathOutputSet + to_string(numOfTest);
    ofstream OutputFile(OutputFileName);
    OutputFile.clear();
    int n;
    int first = 0;
    vector < vector < int > > g;
    vector < int > used;
    int m;
    DataFile>>n>>m;
    g.resize(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        DataFile>>u>>v;
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    DataFile.close();
    vector < int > order(n);
    for (int i = 0; i < n; i++)
        order[i] = i;
    sort(order.begin(), order.end(), [&](int a, int b) {
        return (g[a].size() < g[b].size());
    });
    for (int i = 0; i < n; i++)
        sort(g[i].begin(), g[i].end(), [&](int a, int b) {
            return (g[a].size() < g[b].size());
        });
    used.resize(n, 0);
    used[order[0]] = 1;
    first = order[0];
    bool isfind = false;
    Rec(OutputFile, g, used, order[0], 1, 1, 0, n, beat, order[0], isfind);
    if (OutputFile.is_open()) {
        OutputFile.close();
    }
}