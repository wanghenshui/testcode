#include <iostream>
#include <cstdio>
#include <cstring>
#include <climits>
using namespace std;
#define MAX 100005

long long a[MAX];
long long b[MAX];

int main () {
    int T;
    scanf("%d", &T);
    for (int t=1; t<=T; t++) {
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        int n, k;
        scanf("%d%d", &n, &k);
        for (int i = 0; i < n; i++)
            scanf("%d", &a[i]);
        for (int i = 0; i < n; i++)
            scanf("%d", &b[i]);
        a[0] = a[0] + b[0];
        int count = 0;
        for (int i = 1; i < n; i++)
            if (a[i]>a[0]) count++;
        if (count < k)
            printf("Yes\n");
        else
            printf("No\n");
    }
}
