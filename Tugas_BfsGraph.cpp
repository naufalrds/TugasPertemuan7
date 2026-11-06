#include <iostream>
#include <queue>
using namespace std;

const int N = 6;

int adj[N][N] = {0};

int main() {
    int jumlahEdge;
    cout << "Jumlah edge: ";
    cin >> jumlahEdge;

    cout << "Masukkan edge (contoh: A B):\n";
    for (int i = 0; i < jumlahEdge; i++) {
        char u, v;
        cout << "Edge " << i + 1 << ": ";
        cin >> u >> v;
        u = toupper(u);
        v = toupper(v);
        int a = u - 'A', b = v - 'A';
        if (a < 0 || a >= N || b < 0 || b >= N) {
            cout << "Vertex tidak valid (gunakan A-F)!\n";
            i--;
            continue;
        }
        adj[a][b] = adj[b][a] = 1;
    }

    cout << "\nAdjacency Matrix:\n  ";
    for (int i = 0; i < N; i++) cout << char('A' + i) << " ";
    cout << "\n";
    for (int i = 0; i < N; i++) {
        cout << char('A' + i) << " ";
        for (int j = 0; j < N; j++) cout << adj[i][j] << " ";
        cout << "\n";
    }

    char awal;
    cout << "\nVertex awal: ";
    cin >> awal;
    awal = toupper(awal);
    int start = awal - 'A';
    if (start < 0 || start >= N) {
        cout << "Vertex tidak valid!\n";
        return 1;
    }

    bool visited[N] = {false};
    queue<int> q;
    visited[start] = true;
    q.push(start);

    cout << "Urutan BFS: ";
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        cout << char('A' + cur) << " ";
        for (int i = 0; i < N; i++) {
            if (adj[cur][i] && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
    cout << endl;
    return 0;
}
