
struct Hash {
    static uint64_t mix(uint64_t x) {
        static const uint64_t rand=chrono::steady_clock::now().time_since_epoch().count();
        x+=rand;
        x^=x>>30;
        x*=0xbf58476d1ce4e5b9;
        x^=x>>27;
        x*=0x94d049bb133111eb;
        return x^(x>>31);
    }

    static void comb(size_t& seed,size_t val) {
        seed^=val+0x9e3779b97f4a7c15+(seed<<12)+(seed>>4);
    }

    size_t operator()(uint64_t x) const {
        return mix(x);
    }

    template<typename T,size_t N>
    size_t operator()(const array<T,N>& a) const {
        size_t seed=0;
        for (const auto& i : a) comb(seed,mix(i));
        return seed;
    }

    template<typename T>
    size_t operator()(const vector<T>& v) const {
        size_t seed=0;
        for (const auto& i : v) comb(seed,mix(i));
        return seed;
    }
};

unordered_map<int,int,Hash> mp;
unordered_map<array<int,2>,int,Hash> mp;
unordered_map<vector<int>,int,Hash> mp;
