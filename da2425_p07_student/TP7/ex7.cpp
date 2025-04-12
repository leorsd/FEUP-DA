
#include <algorithm>

#include "exercises.h"
bool Activity::overlaps(const Activity &a2) const {
    return !(finish <= a2.start || a2.finish <= start);
}

bool Activity::operator==(const Activity &a2) const {
    return finish == a2.finish && start == a2.start;
}

bool Activity::operator<(const Activity &a2) const {
    return finish < a2.finish;
}

void activityRecur(std::vector<Activity>& A, std::vector<Activity>& current, std::vector<Activity>& best, unsigned int index) {
    if (index == A.size()) {
        if (current.size() > best.size()) {
            best = current;
        }
        return;
    }

    activityRecur(A, current, best, index + 1);

    if (current.empty() || A[index].start >= current.back().finish) {
        current.push_back(A[index]);
        activityRecur(A, current, best, index + 1);
        current.pop_back(); // backtrack
    }
}

std::vector<Activity> activitySelectionBT(std::vector<Activity> A) {
    std::sort(A.begin(), A.end());
    std::vector<Activity> current, best;
    activityRecur(A, current, best, 0);
    return best;
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

TEST(TP7_Ex7, activityScheduling) {
    std::vector<Activity> A = {{10,20}, {30, 35}, {5, 15}, {10, 40}, {40, 50}};
    std::vector<Activity> V = activitySelectionBT(A);
    EXPECT_EQ(V.size(), 3 );
    EXPECT_EQ(noOverlaps(V), true);
}
