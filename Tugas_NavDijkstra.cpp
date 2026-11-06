#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

const int N = 6;
const int INF = INT_MAX;

int graph[N][N] = {0};

void tambahJalan(char u, char v, int w) {
    int a = u - 'A', b = v - 'A';
    graph[a][b] = graph[b][a] = w;
}

void dijkstra(int src, int dist[], int prev[]) {
    bool visited[N] = {false};
    for (int i = 0; i < N; i++) {
        dist[i] = INF;
        prev[i] = -1;
    }
    dist[src] = 0;

    for (int count = 0; count < N; count++) {
        int u = -1;
        for (int i = 0; i < N; i++)
            if (!visited[i] && (u == -1 || dist[i] < dist[u])) u = i;
        if (u == -1 || dist[u] == INF) break;
        visited[u] = true;

        for (int v = 0; v < N; v++) {
            if (graph[u][v] && !visited[v] && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                prev[v] = u;
            }
        }
    }
}

void cetakRute(int prev[], int tujuan) {
    vector<int> rute;
    for (int v = tujuan; v != -1; v = prev[v]) rute.push_back(v);
    reverse(rute.begin(), rute.end());
    for (size_t i = 0; i < rute.size(); i++) {
        cout << char('A' + rute[i]);
        if (i + 1 < rute.size()) cout << " -> ";
    }
}

int main() {
    // data jarak antar lokasi (km)
    tambahJalan('A', 'B', 4);
    tambahJalan('A', 'C', 2);
    tambahJalan('B', 'C', 1);
    tambahJalan('B', 'D', 5);
    tambahJalan('B', 'E', 3);
    tambahJalan('C', 'D', 8);
    tambahJalan('C', 'E', 6);
    tambahJalan('D', 'E', 2);
    tambahJalan('D', 'F', 4);
    tambahJalan('E', 'F', 3);

    int dist[N], prev[N];

    // bag 1 : rute terpendek dari A ke semua lokasi
    dijkstra(0, dist, prev);
    cout << "=== Rute terpendek dari lokasi A ke semua lokasi ===\n";
    for (int i = 1; i < N; i++) {
        cout << "A ke " << char('A' + i) << " : ";
        cetakRute(prev, i);
        cout << " (Total jarak: " << dist[i] << " km)\n";
    }

    // bag 2 : rekomendasi rute berdasarkan input pengguna
    char asal, tujuan;
    cout << "\n=== Rekomendasi Rute Tercepat ===\n";
    cout << "Lokasi asal (A-F)   : ";
    cin >> asal;
    cout << "Lokasi tujuan (A-F) : ";
    cin >> tujuan;
    asal = toupper(asal);
    tujuan = toupper(tujuan);

    int s = asal - 'A', t = tujuan - 'A';
    if (s < 0 || s >= N || t < 0 || t >= N) {
        cout << "Lokasi tidak valid!\n";
        return 1;
    }

    dijkstra(s, dist, prev);
    if (dist[t] == INF) {
        cout << "Tidak ada rute dari " << asal << " ke " << tujuan << endl;
    } else {
        cout << "Rute tercepat: ";
        cetakRute(prev, t);
        cout << "\nTotal jarak  : " << dist[t] << " km\n";
    }
    return 0;
}
