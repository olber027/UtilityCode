//
// Created by molberding on 9/13/2017.
//

#ifndef UTILITYCODE_SET_H
#define UTILITYCODE_SET_H

#include <vector>

namespace set {

    template<typename T>
    class Set {
    private:
        std::vector<T> items;

        void forceAdd(T item) {
            items.push_back(item);
        }
    public:
        Set() : items(std::vector<T>()) {}

        Set(T* list, int size) {
            items = std::vector<T>();
            for(int i = 0; i < size; i++) {
                addItem(list[i]);
            }
        }

        Set(std::vector<T> list) {
            items = std::vector<T>();
            for(int i = 0; i < list.size(); i++) {
                addItem(list[i]);
            }
        }

        Set(const Set<T>& set) {
            items = std::vector<T>();
            for(int i = 0; i < set.items.size(); i++) {
                items.push_back(set.items[i]);
            }
        }

        ~Set() {}

        Set<T>& operator=(const Set<T>& set) {
            items = std::vector<T>();
            for(int i = 0; i < set.items.size(); i++) {
                items.push_back(set.items[i]);
            }
        }

        bool contains(T item) {
            for(int i = 0; i < items.size(); i++) {
                if(items[i] == item) {
                    return true;
                }
            }
            return false;
        }

        bool addItem(T item) {
            if(!contains(item)) {
                items.push_back(item);
                return true;
            }
            return false;
        }

        bool removeItem(T item) {
            for(int i = 0; i < size(); i++) {
                if(items[i] == item) {
                    items.erase(items.begin() + i);
                    return true;
                }
            }
            return false;
        }

        T operator[](int index) {
            return items[index];
        }

        int size() {
            return items.size();
        }

        Set<T> Union(Set<T> other) {
            Set<T> result = Set<T>();
            for(int i = 0; i < size(); i++) {
                //bypass addItem since we know every element of this set to be unique already.
                result.forceAdd(items[i]);
            }
            for(int i = 0; i < other.size(); i++) {
                result.addItem(other[i]);
            }
            return result;
        }

        Set<T> Intersection(Set<T> other) {
            Set<T> result = Set<T>();
            for(int i = 0; i < size(); i++) {
                if(other.contains(items[i])) {
                    result.forceAdd(items[i]);
                }
            }
            return result;
        }

        Set<T> Complement(Set<T> other) {
            Set<T> result = Set<T>();
            for(int i = 0; i < size(); i++) {
                if(!other.contains(items[i])) {
                    result.forceAdd(items[i]);
                }
            }
            return result;
        }

        Set<T> operator+(Set<T> other) {
            return Union(other);
        }

        Set<T> operator-(Set<T> other) {
            return Complement(other);
        }

        Set<T> operator+=(Set<T> other) {
            for(int i = 0; i < other.size(); i++) {
                addItem(other[i]);
            }
            return *this;
        }

        Set<T> operator-=(Set<T> other) {
            Set<T> temp = Complement(other);
            *this = temp;
            return *this;
        }

        bool isSubSet(Set<T> other) {
            for(int i = 0; i < size(); i++) {
                if(!other.contains(items[i])) {
                    return false;
                }
            }
            return true;
        }

        bool isSuperSet(Set<T> other) {
            for(int i = 0; i < other.size(); i++) {
                if(!contains(other[i])) {
                    return false;
                }
            }
            return true;
        }
    };
}

#endif //UTILITYCODE_SET_H
