#ifndef CACHE_H
#define CACHE_H

#include <cmath>

int const MEM_SIZE = 512*1024;
int const CACHE_LINE_SIZE = 32;
int const CACHE_TAG_LEN = 10;
int const CACHE_LINE_COUNT = 64;


int const ADDR_LEN = int(log2(MEM_SIZE));
int const CACHE_OFFSET_LEN = int(log2(CACHE_LINE_SIZE));
int const CACHE_IDX_LEN = ADDR_LEN - CACHE_OFFSET_LEN - CACHE_TAG_LEN;
int const CACHE_WAY = 4;// CACHE_LINE_COUNT >> CACHE_IDX_LEN (массив не разрешил вставить в качестве длины формулу)
int const CACHE_SETS_COUNT = CACHE_LINE_COUNT / CACHE_WAY;


class Cache {
public:
    explicit Cache(bool is);

    bool find (int addr, bool W_R);

    bool checkWrite (int set, int tag);
    bool checkRead (int set, int tag);
    void missed (int set, int tag, bool W_R);

    void hit ();
    void miss ();

    static int getTag (int addr);
    static int getSet (int addr);
    [[nodiscard]] int getReq() const;
    [[nodiscard]] int getHit() const;
    [[nodiscard]] int getTime() const;

    int LRU(int set);
    void LRUupd(int set);
    int bit_pLRU(int set);
    void bit_pLRUupd(int set, int idx);

    void addTime(int num);

private:
    int tags[CACHE_SETS_COUNT][CACHE_WAY]{}, lru[CACHE_SETS_COUNT][CACHE_WAY]{};
    bool mas[CACHE_SETS_COUNT][CACHE_WAY]{}, mod[CACHE_SETS_COUNT][CACHE_WAY]{};
    int requestCount, hitCount, time;
    bool is_lru; // 1 - LRU, 0 - bit_pLRU
};


#endif //CACHE_H
