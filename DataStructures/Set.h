//
// Created by molberding on 9/13/2017.
//

#ifndef UTILITYCODE_SET_H
#define UTILITYCODE_SET_H

#include "TypeTraits.h"
#include <vector>

namespace Utilities
{
    template <typename T>
    class Set
    {
        static_assert(is_equal_comparable<T>::value, "Type T must be comparable with the == operator");

        struct Iterator
        {
            using iterator_category = typename std::vector<T>::iterator::iterator_category;
            using difference_type   = typename std::vector<T>::iterator::difference_type;
            using value_type        = typename std::vector<T>::iterator::value_type;
            using pointer           = typename std::vector<T>::iterator::pointer;
            using reference         = typename std::vector<T>::iterator::reference;

            Iterator(typename std::vector<T>::iterator pos) : it(pos) {}

            reference operator*() const { return *it; }
            pointer operator->() { return it; }

            // Prefix increment
            Iterator& operator++() { return ++it; }

            // Postfix increment
            Iterator operator++(int) { Iterator tmp = *this; it++; return tmp; }

            friend bool operator== (const Iterator& a, const Iterator& b) { return a.it == b.it; };
            friend bool operator!= (const Iterator& a, const Iterator& b) { return a.it != b.it; };

        private:
            typename std::vector<T>::iterator it;
        };

    private:
        std::vector<T> items;

        void forceAdd(const T& item)
        {
            items.push_back(item);
        }

    public:
        Set() : items(std::vector<T>()) {}
        Set(const T* list, int size)
        {
            items = std::vector<T>();
            for(int i = 0; i < size; i++)
            {
                addItem(list[i]);
            }
        }
        explicit Set(const std::vector<T>& list)
        {
            items = std::vector<T>();
            for(int i = 0; i < list.size(); i++)
            {
                addItem(list[i]);
            }
        }
        Set(const Set<T>& set)
        {
            items = std::vector<T>();
            for(int i = 0; i < set.items.size(); i++)
            {
                items.push_back(set.items[i]);
            }
        }
        ~Set() = default;

        Set<T>& operator=(const Set<T>& set)
        {
            if(this != &set)
            {
                items = std::vector<T>(set.items);
            }
        }

        T operator[](const int index) const
        {
            return items[index];
        }

        bool operator==(const Set<T>& rhs) const
        {
            if(size() != rhs.size())
            {
                return false;
            }
            for(int i = 0; i < size(); i++)
            {
                if(!contains(rhs[i]) || !contains(items[i]))
                {
                    return false;
                }
            }
            return true;
        }

        int getIndexOf(const T& item) const
        {
            for(int i = 0; i < size(); i++)
            {
                if(items[i] == item)
                {
                    return i;
                }
            }
            return -1;
        }

        bool contains(const T& item) const
        {
            return getIndexOf(item) >= 0;
        }

        bool addItem(const T& item)
        {
            int index = getIndexOf(item);
            if(index >= 0)
            {
                return false;
            }
            items.push_back(item);
            return true;
        }

        bool removeItem(const T& item)
        {
            return removeItem(getIndexOf(item));
        }

        bool removeItem(const int index)
        {
            if(index < 0 || index >= items.size())
            {
                return false;
            }
            items.erase(items.begin() + index);
            return true;
        }

        int size() const
        {
            return items.size();
        }

        //Provides the union of two sets.
        //e.g. {1, 2} U {2, 3} = {1, 2, 3}
        Set<T> Union(const Set<T>& other) const
        {
            Set<T> result = *this;
            for(int i = 0; i < other.size(); i++)
            {
                result.addItem(other[i]);
            }
            return result;
        }

        //provides the intersection of two sets.
        //e.g. {1, 2} I {2, 3} = {2}
        Set<T> Intersection(const Set<T>& other) const
        {
            Set<T> result = Set<T>();
            for(int i = 0; i < size(); i++)
            {
                if(other.contains(items[i]))
                {
                    result.forceAdd(items[i]);
                }
            }
            return result;
        }

        // provides the complement of the calling set
        // with regards to the set passed in.
        // e.g. {1, 2} / {2, 3} = {1, 3}
        Set<T> Complement(const Set<T>& other) const
        {
            Set<T> result = Set<T>();
            for(int i = 0; i < size(); i++)
            {
                if(!other.contains(items[i]))
                {
                    result.forceAdd(items[i]);
                }
            }
            for(int i = 0; i < other.size(); i++)
            {
                if(!contains(other[i]))
                {
                    result.addItem(other[i]);
                }
            }
            return result;
        }

        Set<T> operator+(const Set<T>& other) const
        {
            return Union(other);
        }

        Set<T> operator-(const Set<T>& other) const
        {
            return Complement(other);
        }

        Set<T>& operator+=(const Set<T>& other)
        {
            for(int i = 0; i < other.size(); i++)
            {
                addItem(other[i]);
            }
            return *this;
        }

        Set<T>& operator-=(const Set<T>& other)
        {
            Set<T> temp = Complement(other);
            *this       = temp;
            return *this;
        }

        bool isSubSetOf(const Set<T>& other) const
        {
            for(int i = 0; i < size(); i++)
            {
                if(!other.contains(items[i]))
                {
                    return false;
                }
            }
            return true;
        }

        bool isSuperSetOf(const Set<T>& other) const
        {
            for(int i = 0; i < other.size(); i++)
            {
                if(!contains(other[i]))
                {
                    return false;
                }
            }
            return true;
        }

        std::vector<T> toVector() const
        {
            return std::vector<T>(items);
        }

        T* toArray() const
        {
            T* result = new T[size()];
            for(int i = 0; i < size(); i++)
            {
                result[i] = items[i];
            }
            return result;
        }
    };
}// namespace Utilities

#endif//UTILITYCODE_SET_H
