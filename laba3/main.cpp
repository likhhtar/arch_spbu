#include "problem.h"

int main() {
    auto lru_cache = mmul(true);
    auto bit_plru_cache = mmul(false);
    printf("LRU:\thit perc. %3.4f%%\ttime: %u\npLRU:\thit perc. %3.4f%%\ttime: %u\n",
           (double) ((double)lru_cache->getHit()  / (double)lru_cache->getReq() * 100), lru_cache->getTime(),
           (double) ((double)bit_plru_cache->getHit()  / (double)bit_plru_cache->getReq() * 100), bit_plru_cache->getTime());
    return 0;
}