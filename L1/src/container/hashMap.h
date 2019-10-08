#pragma once

#include "exception.h"
#include <algorithm>
#include <iostream>
#include <functional>
#include <string>

#define SIZE 2000000

namespace pavel {
    template<typename Key>
    unsigned int defaultHash(Key key) {
        return static_cast<unsigned int>(key) % SIZE;
    }

    template<typename Key>
    bool defaultCompare(const Key& v1, const Key& v2) {
        return  v1 == v2;
    }

    template <typename Key, typename Value>
    class HashMap;

    template <typename Key, typename Value>
    class HashNode {
    public:
        explicit HashNode(const Key& key, const Value& value): key(key), value(value) {}

        HashNode (HashNode& node): key(node.key), value(node.value) {}

        friend void swap(HashNode& a, HashNode& b){
            std::swap(a.key, b.key);
            std::swap(a.value, b.value);
        }

        HashNode& operator=(const HashNode& other) {
            swap(*this, other);
            return *this;
        }

        HashNode& operator=(HashNode&& other) noexcept {
            swap(*this, other);
        }

        [[nodiscard]] const Value& getValue() {
            return value;
        }

        void setValue(Value newValue) {
            value = newValue;
        }

        [[nodiscard]] const Key& getKey() {
            return key;
        }

        [[nodiscard]] HashNode *getNext() const {
            return next;
        }

        void setNext(HashNode *newNext) {
            next = newNext;
        }

    private:
        Key key;
        Value value;
        HashNode* next = nullptr;
    };

    template <typename Key, typename Value>
    class HashMapIterator {
    public:
        explicit HashMapIterator(const HashMap<Key, Value>& hashMap,
                HashNode<Key, Value>* node = nullptr)
                :hashMap(hashMap), currentNode(node), compareFunc(hashMap.compareFunc) {
            if (node == nullptr) {
                getNext();
            } else {
                currentValue = hashMap.hashFunc(node->getKey());
            }
        }

        HashMapIterator(HashMapIterator& it)
        : HashMapIterator(it.hashMap, it.currentNode)
        {
            compareFunc = it.compareFunc;
        }

        HashMapIterator&operator++() {
            getNext();
            return *this;
        }

        HashMapIterator operator++(int) {
            auto ret = HashMapIterator(*this);
            getNext();
            return ret;
        }

        const Key& key() {
            return currentNode->getKey();
        }

        const Value& value() {
            return currentNode->getValue();
        }

        bool end(){
            return currentValue >= SIZE - 1;
        }

        friend bool operator==(const HashMapIterator<Key, Value>& it1,
                               const HashMapIterator<Key, Value>& it2) {
            return it1.compareFunc(it1.currentNode->getKey(), it2.currentNode->getKey());
        }

        friend bool operator!=(const HashMapIterator<Key, Value>& it1,
                               const HashMapIterator<Key, Value>& it2) {
            return !it1.compareFunc(it1.currentNode->getKey(), it2.currentNode->getKey());
        }
    private:
        void getNext() {
            if (currentNode != nullptr) {
                currentNode = currentNode->getNext();
            }
            while (currentNode == nullptr && (currentValue < SIZE - 1)) {
                currentValue++;
                currentNode = hashMap.table[currentValue];
            }
        }

        std::function<int(Key, Key)> compareFunc;
        const HashMap<Key, Value>& hashMap;
        HashNode<Key, Value>* currentNode = nullptr;
        unsigned int currentValue = 0;
    };


    template<typename Key, typename Value>
    class HashMap {
        template <typename K, typename V>
        friend class HashMapIterator;
    public:
            explicit HashMap(
                    const std::function<unsigned int(Key)>& hash = defaultHash<Key>,
                    const std::function<int(Key, Key)>& compare = defaultCompare<Key>)
                    : hashFunc(hash), compareFunc(compare) {
                table = new HashNode<Key, Value>* [SIZE]();
            }

            ~HashMap() {
                for (unsigned int i = 0; i < SIZE; i++) {
                    HashNode<Key, Value> *entry = table[i];
                    while (entry != nullptr) {
                        HashNode<Key, Value> *prev = entry;
                        entry = entry->getNext();
                        delete prev;
                    }
                }
                delete[] table;
            }

            const Value& at(const Key& key) {
                unsigned int hashValue = hashFunc(key);
                HashNode<Key, Value>* node = table[hashValue];

                while (node != nullptr) {
                    if (compareFunc(node->getKey(), key)) {
                        return node->getValue();
                    }
                    node = node->getNext();
                }
                throw ElementNotFoundException<Key>(key);
            }

            bool get(const Key& key, Value& value) {
                try {
                    value = at(key);
                    return true;
                } catch (ElementNotFoundException<Key>& ex) {
                    return false;
                }
            }

            void create(const Key& key, const Value& value) {
                auto [prev, entry, hashValue] = getEntry(key);

                if (entry == nullptr) {
                    entry = new HashNode<Key, Value>(key, value);
                    if (prev == nullptr) {
                        table[hashValue] = entry;
                    } else {
                        prev->setNext(entry);
                    }
                } else {
                    throw ElementAlreadyExistsException<Key, Value>(key, entry->getValue());
                }
            }

            void update(const Key& key, const Value& value) {
                auto [prev, entry, hashValue] = getEntry(key);

                if (entry == nullptr) {
                    entry = new HashNode<Key, Value>(key, value);
                    if (prev == nullptr) {
                        table[hashValue] = entry;
                    } else {
                        prev->setNext(entry);
                    }
                } else {
                    entry->setValue(value);
                }
            }

            void remove(const Key& key) {
                auto [prev, entry, hashValue] = getEntry(key);

                if (entry == nullptr) {
                    throw ElementNotFoundException<Key>(key);
                } else {
                    if (prev == nullptr) {
                        table[hashValue] = entry->getNext();
                    } else {
                        prev->setNext(entry->getNext());
                    }
                    delete entry;
                }
            }

            HashMapIterator<Key, Value> begin(){
                return HashMapIterator<Key, Value>(*this);
            }

            HashMapIterator<Key, Value> end(){
                unsigned int lastHash;
                for (lastHash = SIZE - 1; table[lastHash] == nullptr && lastHash > 0; lastHash--);

                if (lastHash > 0) {
                    HashNode<Key, Value>* node = table[lastHash];
                    while (node->getNext() != nullptr) {
                        node = node->getNext();
                    }
                    return HashMapIterator<Key, Value>(*this, node);
                }
            }

    private:
        std::tuple<HashNode<Key, Value>*, HashNode<Key, Value>*,
                unsigned int>getEntry(const Key& key) {
            unsigned int hashValue = hashFunc(key);

            HashNode<Key, Value> *entry = table[hashValue];
            HashNode<Key, Value>* prev = nullptr;
            while (entry != nullptr && !compareFunc(entry->getKey(), key)) {
                prev = entry;
                entry = entry->getNext();
            }
            return std::make_tuple(prev, entry, hashValue);
        }

        HashNode<Key, Value> **table;
        std::function<unsigned int(Key)> hashFunc;
        std::function<int(Key, Key)> compareFunc;
    };

}
