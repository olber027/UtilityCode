//
// Created by molberding on 9/13/2017.
//

#ifndef UTILITYCODE_SET_H
#define UTILITYCODE_SET_H

#include <vector>

namespace set {
    //Provides basic set functionality, including unions,
    //intersections and complements. Does not allow
    //duplicate elements.
    template<typename T>
    class Set {
    private:
        std::vector<T> items;

        void forceAdd(T item) {
            items.push_back(item);
        }
    public:
        Set() : items(std::vector<T>()) {}

        Set(const T* list, const int size) {
            items = std::vector<T>();
            for(int i = 0; i < size; i++) {
                addItem(list[i]);
            }
        }

        Set(const std::vector<T> list) {
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

        bool contains(const T item) const {
            for(int i = 0; i < items.size(); i++) {
                if(items[i] == item) {
                    return true;
                }
            }
            return false;
        }

        T* addItem(const T item) {
            for(int i = 0; i < items.size(); i++) {
                if(items[i] == item) {
                    return &items[i];
                }
            }
            items.push_back(item);
            return &items[items.size()-1];
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

        T pop() {
            T result = items.back();
            items.pop_back();
            return result;
        }

        T operator[](const int index) const {
            return items[index];
        }

        int size() const {
            return items.size();
        }

        //Provides the union of two sets.
        //e.g. {1, 2} U {2, 3} = {1, 2, 3}
        Set<T> Union(const Set<T>& other) const {
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

        //provides the intersection of two sets.
        //e.g. {1, 2} I {2, 3} = {2}
        Set<T> Intersection(const Set<T>& other) const {
            Set<T> result = Set<T>();
            for(int i = 0; i < size(); i++) {
                if(other.contains(items[i])) {
                    result.forceAdd(items[i]);
                }
            }
            return result;
        }

        // provides the complement of the calling set
        // with regards to the set passed in.
        // e.g. {1, 2, 3} / {2, 3} = {1}
        Set<T> const Complement(const Set<T>& other) const {
            Set<T> result = Set<T>();
            for(int i = 0; i < size(); i++) {
                if(!other.contains(items[i])) {
                    result.forceAdd(items[i]);
                }
            }
            return result;
        }

        Set<T> operator+(const Set<T>& other) const {
            return Union(other);
        }

        Set<T> operator-(const Set<T>& other) const {
            return Complement(other);
        }

        Set<T> operator+=(const Set<T>& other) {
            for(int i = 0; i < other.size(); i++) {
                addItem(other[i]);
            }
            return *this;
        }

        Set<T> operator-=(const Set<T>& other) {
            Set<T> temp = Complement(other);
            *this = temp;
            return *this;
        }

        bool isSubSetOf(const Set<T>& other) const {
            for(int i = 0; i < size(); i++) {
                if(!other.contains(items[i])) {
                    return false;
                }
            }
            return true;
        }

        bool isSuperSetOf(const Set<T>& other) const {
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
