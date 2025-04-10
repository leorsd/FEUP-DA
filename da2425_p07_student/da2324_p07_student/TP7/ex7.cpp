
#include "exercises.h"

std::vector<Activity> activitySelectionBT(std::vector<Activity> A) {
}

/// TESTS ///
#include <gtest/gtest.h>

bool noOverlaps(const std::vector<Activity> &acts) {
    for(unsigned int i = 0; i < acts.size(); i++) {
        Activity A1 = acts.at(i);
        for(unsigned int j = i + 1; j < acts.size(); j++) {
            Activity A2 = acts.at(j);
            if(A1.overlaps(A2)) return false;
        }
    }
    return true;
}


bool Activity::overlaps(const Activity &a2) const {
    return !(finish <= a2.start || a2.finish <= start);
}

TEST(TP7_Ex7, activityScheduling) {
    std::vector<Activity> A = {{10,20}, {30, 35}, {5, 15}, {10, 40}, {40, 50}};
    std::vector<Activity> V = activitySelectionBT(A);
    EXPECT_EQ(V.size(), 3 );
    EXPECT_EQ(noOverlaps(V), true);
}
