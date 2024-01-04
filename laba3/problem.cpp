#include <iostream>
#include "problem.h"

#define M 64
#define N 60
#define K 32
//int a[M][K];
//int b[K][N];
//int c[M][N];

int aSt = 0x40000, aSZ = 1, aSize = M * K * aSZ;
int bSt = aSt + aSize, bSZ = 2, bSize = N * K * bSZ;
int cSt = bSt + bSize, cSZ = 4;


Cache * mmul(bool is_lru) {
    auto cache = new Cache(is_lru);
    int pa = aSt;
    cache->addTime(1); //init

    int pc = cSt;
    cache->addTime(1); //init

    for (int y = 0; y < M; y++)
    {
        cache->addTime(2); //for and <

        for (int x = 0; x < N; x++)
        {
            cache->addTime(2); //for and <

            int pb = bSt;
            cache->addTime(1); //init

            // int s = 0;
            cache->addTime(1); // init

            for (int k = 0; k < K; k++)
            {
                cache->addTime(2); //for and <

                //s += pa[k] * pb[x];

                cache->addTime(1); // a1 c1
                cache -> find(pa + k * aSZ, false);
                cache->addTime(1); // 8 бит, значит, 8 / 16, 1 такт

                cache->addTime(1); // a1 c1
                cache -> find(pb + x * bSZ, false);
                cache->addTime(1); // 16 бит, значит, 16 / 16, 1 такт

                cache->addTime(1); //+
                cache->addTime(5); //*

                pb += N * bSZ;
                cache->addTime(1); //+
            }
            //pc[x] = s;
            cache->addTime(1); // a1 c1
            cache -> find(pc + x * cSZ, true);
            cache->addTime(2); // 32 бит, значит, 32 / 16, 2 такт
        }
        pa += K * aSZ;
        cache->addTime(1); //+

        pc += N * cSZ;
        cache->addTime(1); //+
    }
    cache->addTime(1); //exit func

    return cache;
}
