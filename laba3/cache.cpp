#include "cache.h"

Cache::Cache(bool is) {
    this->hitCount = 0;
    this->requestCount = 0;
    this->time = 0;
    this->is_lru = is;
}

bool Cache::find (int addr, bool W_R) {
    int set = Cache::getSet(addr);
    int tag = Cache::getTag(addr);
    this->requestCount++;

    if (W_R) return this -> checkWrite(set, tag);
    else return this -> checkRead(set, tag);
}

int Cache::getTag (int addr) {
    return (addr >> (CACHE_OFFSET_LEN + CACHE_IDX_LEN));
}

int Cache::getSet (int addr) {
    return (addr >> CACHE_OFFSET_LEN) % CACHE_SETS_COUNT;
}

bool Cache::checkWrite(int set, int tag) {
    for(int i = 0; i < CACHE_WAY; i++) {
        if (tag == this->tags[set][i]) {
            this->hit();
            this->mod[set][i] = true;

            if (this -> is_lru) this->lru[set][i] = 0;
            else this->bit_pLRUupd(set, i);

            return true;
        }
    }

    this->missed(set, tag, true);
    return false;
}

void Cache::missed(int set, int tag, bool W_R) {
    int lru_row;
    if (this -> is_lru) lru_row = this->LRU(set);
    else lru_row = this->bit_pLRU(set);
    this->miss();

    if(W_R && mod[set][lru_row]) {
        addTime(CACHE_LINE_SIZE * 8 / 16); // d2 отправим строку на запись и команду записи параллельно
                                                // (в каждый такт передается 16 бит, а строка хранится в байтах)
        addTime(100); //memory response
    }

    addTime(1); // c2 - отправляет команду, чтобы прочитать значение из памяти
    addTime(100); //memory response
    addTime(CACHE_LINE_SIZE * 8 / 16); // d2 (в каждый такт передается 16 бит, а строка хранится в байтах)

    this->mas[set][lru_row] = true;
    this->tags[set][lru_row] = tag;
    this->mod[set][lru_row] = W_R;
    if (this -> is_lru) this->lru[set][lru_row] = 0;
    else this->bit_pLRUupd(set, lru_row);
}

bool Cache::checkRead(int set, int tag) {
    if (this -> is_lru) this->LRUupd(set);

    for (int i = 0; i < CACHE_WAY; i++) {
        if(tag == this->tags[set][i] && this->mas[set][i]) {
            this->hit();

            if (this -> is_lru) this->lru[set][i] = 0;
            else this->bit_pLRUupd(set, i);
            return true;
        }
    }

    this->missed(set, tag, false);
    return false;
}

void Cache::hit () {
    this -> hitCount++;
    this -> time += 6; // hit
}

void Cache::miss () {
    this -> time += 4; // miss+mem
}

int Cache::getReq() const {
    return this -> requestCount;
}

int Cache::getHit() const {
    return this -> hitCount;
}

int Cache::getTime() const {
    return this -> time;
}

int Cache::LRU(int set) {
    int maxLRU = -1, idx = -1;
    for (int i = 0; i < CACHE_WAY; i++) {
        if (this->lru[set][i] > maxLRU) {
            maxLRU = this->lru[set][i];
            idx = i;
        }
    }
    return idx;
}

void Cache::LRUupd(int set) {
    for (int i = 0; i < CACHE_WAY; i++) {
        this->lru[set][i]++;
    }
}

int Cache::bit_pLRU(int set) {
    for (int i = 0; i < CACHE_WAY; i++) {
        if (this->lru[set][i] == 0) {
            return i;
        }
    }
    this->bit_pLRUupd(set, 0);
    return 0;
}

void Cache::bit_pLRUupd(int set, int idx) {
    bool all = true;
    for (int i = 0; i < CACHE_WAY; i++) {
        if (i == idx) this->lru[set][i] = 1;
        else if (this->lru[set][i] == 0) all = false;
    }
    if(all) {
        for (int i = 0; i < CACHE_WAY; i++) {
            if (i != idx) this->lru[set][i] = 0;
        }
    }
}

void Cache::addTime(int num) {
    this->time += num;
}

