#include <bits/stdc++.h>

using namespace std;

int main() {
    for(int T = 0; T < 10000; ++T) {
        system(".\\random.exe > .\\data.in");
        double st = clock();
        system(".\\sol.exe < .\\data.in > .\\data.ans");
        double et = clock();
        system(".\\bf.exe < .\\data.in > .\\data.out");
        if(system("fc C:\\Users\\Xian\\Desktop\\check\\data.ans C:\\Users\\Xian\\Desktop\\check\\data.out")) {
            puts("Wrong Answer");
            return 0;
        } else {
            printf("Accepted, Case #%d, Time %.0lfms\n", T, et - st);
        }
    }
    return 0;
}