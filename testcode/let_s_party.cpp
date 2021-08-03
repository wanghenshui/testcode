#include <iostream>
#include <cstdio>
#include <cstring>
#include <climits>
using namespace std;
#define MAX 100005

long long a[MAX];

int main () {
    int T;
    scanf("%d", &T);
    for (int t=1; t<=T; t++) {
        memset(a, 0, sizeof(a));
        int n, k;
        scanf("%d%d", &n, &k);
        for (int i = 0; i < n; i++)
            scanf("%d", &a[i]);

        if (k == 1 || n < 2) {
            printf("%d %d\n", k, a[0]);
            continue;
        }
        bool equal = true;
        for (int i = 0; i < n; i++) {
            equal = (a[0] == a[i]);
            if (!equal) break;
        }
        
        if (equal) {
            printf("%d %d\n", k, a[0]);
            continue;
        }


        int count = 0;
        int index = 0;
        int value = 0;
        for (int i = 0; i < 2 * n  ; i++) {
            int l = i;
            int m = i + 1;
            if (l >= n) {
                l = i - n;
            }
            if (m >= n) {
                m = i + 1 - n;
            }
            if (a[l] == a[m]) {
                count++;
                index = i;
                value = a[l];
                if (count == k - 1) {
                    printf("%d %d\n", index+2, value);
                    break;
                }
            } else {
                count = 0;
            }
            //printf("%d %d %d %d %d \n", i, l, m, a[l], count);
        }
        if (count == 0)
            printf("INF\n");
    }
}
