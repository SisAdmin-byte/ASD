#include <gtest/gtest.h>
#include "DSU.h"




TEST(DSUTest, BasicUnion) {
    DSU dsu(10);
    dsu.unite(0, 1);
    EXPECT_EQ(dsu.find(0), dsu.find(1));

    dsu.unite(2, 3);
    EXPECT_EQ(dsu.find(2), dsu.find(3));

    EXPECT_NE(dsu.find(0), dsu.find(2));
    EXPECT_NE(dsu.find(1), dsu.find(3));
}

TEST(DSUTest, TransitiveUnion) {
    DSU dsu(10);
    dsu.unite(0, 1);
    dsu.unite(1, 2);

    EXPECT_EQ(dsu.find(0), dsu.find(1));
    EXPECT_EQ(dsu.find(1), dsu.find(2));
    EXPECT_EQ(dsu.find(0), dsu.find(2));
}

TEST(DSUTest, MultipleUnions) {
    DSU dsu(10);
    dsu.unite(0, 1);
    dsu.unite(2, 3);
    dsu.unite(0, 2);

    EXPECT_EQ(dsu.find(0), dsu.find(1));
    EXPECT_EQ(dsu.find(0), dsu.find(2));
    EXPECT_EQ(dsu.find(0), dsu.find(3));
}

TEST(DSUTest, SelfUnion) {
    DSU dsu(10);
    int original_root = dsu.find(5);
    dsu.unite(5, 5);
    EXPECT_EQ(dsu.find(5), original_root);
}


TEST(DSUTest, RankTest) {
    DSU small_dsu(3);

    small_dsu.unite(0, 1);
    small_dsu.unite(0, 2);

    EXPECT_EQ(small_dsu.find(0), small_dsu.find(1));
    EXPECT_EQ(small_dsu.find(0), small_dsu.find(2));
}