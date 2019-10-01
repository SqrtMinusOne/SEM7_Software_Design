#pragma once

#define SIZE 4294967295

namespace pavel {
    auto default_hash = [](auto key) -> unsigned long {return reinterpret_cast<unsigned long>(key) % SIZE;};

    template<typename Key,
            typename Value,
            typename HashFunc = decltype(default_hash)>
    class HashMap {
        public:
            HashMap();
    };
}
