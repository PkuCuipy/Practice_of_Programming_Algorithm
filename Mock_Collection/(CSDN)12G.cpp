#include <iostream>
using namespace std;


int used[20];

int W, n, ans = (1 << 30);
int item[20];
int bag[20];



void dfs(int x, int sum) {
    if (sum >= ans) return;
    if (x == n) {
        ans = min(ans, sum);
        return;
    }
    for (int i = 0; i < sum; ++i) {
        if (bag[i] >= item[x]) {
            bag[i] -= item[x];
            dfs(x + 1, sum);
            bag[i] += item[x];
        }
    }
    bag[sum] -= item[x];
    dfs(x + 1, sum + 1);
    bag[sum] += item[x];
}
int main() {
    cin >> n >> W;
    for (int i = 0; i < n; ++i) {
        cin >> item[i];
        bag[i] = W;
    }
    dfs (0, 1);
    cout << ans << endl;

    return 0;
}

