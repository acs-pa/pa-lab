#pragma once

#include <bits/stdc++.h>
using namespace std;

// numarul maxim de noduri
#define NMAX 1005

// valoare mai mare decat orice distanta din graf
#define INF (1 << 30)

// structura folosita pentru a stoca distanta, cat si vectorul de parinti
// folosind algoritmul Dijkstra
struct DijkstraResult {
    vector<int> d;
    vector<int> p;

    DijkstraResult(const vector<int>& d, const vector<int>& p)
        : d(d)
        , p(p) { }
};

// structura folosita pentru a stoca distanta, vectorul de parinti
// si daca s-a intalnit un ciclu de cost negativ folosind algoritmul
// Bellman-Ford
struct BellmanFordResult {
    bool has_cycle;
    vector<int> d;
    vector<int> p;

    BellmanFordResult(bool has_cycle, const vector<int>& d, const vector<int>& p)
        : has_cycle(has_cycle)
        , d(d)
        , p(p) { }
};

// structura folosita pentru a stoca matricea de distante, matricea
// de parinti si daca s-a intalnit un ciclu de cost negativ
// folosind algoritmul lui Johnson.
struct JohnsonResult {
    vector<vector<int>> d;
    vector<vector<int>> p;
    bool has_cycle;

    JohnsonResult(bool has_cycle, const vector<vector<int>>& d, const vector<vector<int>>& p)
        : has_cycle(has_cycle)
        , d(d)
        , p(p) { }
};

struct Edge {
    int node;
    int neigh;
    int w;

    Edge() { }
    Edge(int node, int neigh, int w)
        : node(node)
        , neigh(neigh)
        , w(w) { }
};

DijkstraResult dijkstra(int source, int nodes, vector<pair<int, int>> adj[NMAX]) {
    // Initializam vectorul de distante cu distante infinite.
    vector<int> d(nodes + 1, INF);
    vector<int> p(nodes + 1, 0);

    // In loc de un priority_queue<> folosim set<>, cu elemente tupluri de
    // tipul (distanta pana la nod, nod). Setul tine elementele ordonate, deci
    // mereum in pq.begin() vom avea tuplul care ii corespunde nodului cu
    // distanta minima.
    set<pair<int, int>> pq;

    // Inseram nodul de plecare in coada si ii actualizam distanta.
    d[source] = 0;
    pq.insert({d[source], source});

    while (!pq.empty()) {
        // Scoatem top-ul.
        auto top = pq.begin();
        const auto [_, node] = *top;
        pq.erase(top);

        // Ii parcurgem toti vecinii.
        for (const auto& [neigh, w] : adj[node]) {
            // Se imbunatateste distanta?
            if (d[node] + w < d[neigh]) {
                // Scoatem vechea pereche/distanta din set.
                pq.erase({d[neigh], neigh});

                // Actualizam distanta si parintele.
                d[neigh] = d[node] + w;
                p[neigh] = node;

                // Inseram noua distanta.
                pq.insert({d[neigh], neigh});
            }
        }
    }

    // Toate nodurile catre care distanta este inca INF nu pot fi atinse din
    // nodul source, deci le setam pe -1.
    for (int node = 1; node <= nodes; node++) {
        if (d[node] == INF) {
            d[node] = -1;
        }
    }

    return {d, p};
}

BellmanFordResult bellman(int source, int nodes, vector<Edge>& edges) {
    // Initializam vectorul de distante cu distante infinite.
    vector<int> d(nodes + 1, INF);
    vector<int> p(nodes + 1, 0);

    // Setez sursa la distanta 0.
    d[source] = 0;

    // Fac N - 1 relaxari.
    for (int i = 1; i <= nodes - 1; i++) {
        // Parcurg toate muchiile:
        for (const auto& [node, neigh, w] : edges) {
            // Se imbunatateste distanta?
            if (d[node] + w < d[neigh]) {
                // Actualizam distanta si parintele.
                d[neigh] = d[node] + w;
                p[neigh] = node;
            }
        }
    }

    // Verific daca mai poate fi updatata distanta.
    for (const auto& [node, neigh, w] : edges) {
        // Se imbunatateste distanta?
        if (d[node] + w < d[neigh]) {
            // Am gasit un ciclu de cost negativ.
            return {true, {}, {}};
        }
    }

    // Toate nodurile catre care distanta este inca INF nu pot fi atinse din
    // nodul source, deci le setam pe -1.
    for (int node = 1; node <= nodes; node++) {
        if (d[node] == INF) {
            d[node] = -1;
        }
    }

    return {false, d, p};
}
