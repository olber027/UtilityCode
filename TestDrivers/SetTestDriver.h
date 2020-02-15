//
// Created by molberding on 1/15/2018.
//

#ifndef UTILITYCODE_SETTESTDRIVER_H
#define UTILITYCODE_SETTESTDRIVER_H

#include "../DataStructures/Set.h"
#include "TestDriver.h"

using namespace set;

class SetTestDriver : public TestDriver {
private:
    class TestItem {
    public:
        explicit TestItem(int d) : data(d) {}
        int data;
    };

public:
    SetTestDriver() {
        init("Set");
    }

    void run() override {
        Set<int> set;
        set.addItem(1);
        assert(1, set.size());
        set.addItem(2);
        assert(2, set.size());
        set.addItem(3);
        assert(3, set.size());
        set.addItem(3);
        assert(3, set.size());

        Set<int> other;
        other.addItem(3);
        other.addItem(4);
        other.addItem(5);

        Set<int> result;
        result = set.Union(other);
        for(int i = 1; i < 6; i++) {
            assert(i, result[i-1]);
        }

        result = set + other;
        for(int i = 1; i < 6; i++) {
            assert(i, result[i-1]);
        }

        result = other.Union(set);
        for(int i = 1; i < 6; i++) {
            assert(true, result.contains(i));
        }

        result = set.Intersection(other);
        assert(1, result.size());
        assert(3, result[0]);

        result = other - set;
        assert(4, result.size());
        assert(1, result[2]);
        assert(2, result[3]);
        assert(4, result[0]);
        assert(5, result[1]);

        result = set.Complement(other);
        assert(1, result[0]);
        assert(2, result[1]);
        assert(4, result[2]);
        assert(5, result[3]);


        assert(true, result.isSubSetOf(set + other));
        assert(true, result.isSuperSetOf(set - other));
        assert(false, result.isSuperSetOf(set));
        assert(false, result.isSubSetOf(set));

        set += other;
        for(int i = 1; i < 6; i++) {
            assert(i, set[i-1]);
        }

        set -= other;
        assert(1, set[0]);
        assert(2, set[1]);

        std::vector<int> nums = {1,1,1,1,2,3,4,5,6,6,6,7,7};
        Set<int> vecSet = Set<int>(nums);
        assert(7, vecSet.size());
        for(int i = 0; i < vecSet.size(); i++) {
            assert(i+1, vecSet[i]);
        }

        int ints[13] = {1,1,1,1,2,3,4,5,6,6,6,7,7};
        Set<int> arrSet = Set<int>(ints, 13);
        assert(7, arrSet.size());
        for(int i = 0; i < arrSet.size(); i++) {
            assert(i+1, arrSet[i]);
        }
        assert(true, vecSet == arrSet);
        assert(false, vecSet == set);
    }

};

#endif //UTILITYCODE_SETTESTDRIVER_H
