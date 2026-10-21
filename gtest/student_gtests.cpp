#include <gtest/gtest.h>

#include "string.hpp"

TEST(StringFunction, strlen) {
    EXPECT_EQ(String::strlen(""), 0);
    EXPECT_EQ(String::strlen("foo"), 3);
}

TEST(StringFunction, strcpy) {
    char result[10];
    EXPECT_EQ(String::strcpy(result, "foo"), result);
    EXPECT_STREQ(result, "foo");

    EXPECT_EQ(String::strcpy(result, "a"), result);
    EXPECT_STREQ(result, "a");

    EXPECT_EQ(String::strcpy(result, ""), result);
    EXPECT_STREQ(result, "");
}

TEST(StringFunction, strncpy) {
    EXPECT_TRUE(false);
}

TEST(StringFunction, strcat) {
    EXPECT_TRUE(false);
}

TEST(StringFunction, strncat) {
    EXPECT_TRUE(false);
}

TEST(StringFunction, strcmp) {
    EXPECT_TRUE(false);
}

TEST(StringFunction, strncmp) {
    EXPECT_TRUE(false);
}

TEST(StringFunction, reverse_cpy) {
    EXPECT_TRUE(false);
}

TEST(StringFunction, strchr) {
    EXPECT_TRUE(false);
}

TEST(StringFunction, strstr) {
    EXPECT_TRUE(false);
}

//Self-write tests
TEST(StringInterface, CStringConstructortest) {
    String s("jasonrong");
    EXPECT_EQ(s.size(), 9);
    EXPECT_EQ(s[0], 'j');
    EXPECT_EQ(s[1], 'a');
    EXPECT_EQ(s[2], 's');
    EXPECT_EQ(s[3], 'o');
    String empty;
    EXPECT_EQ(empty.size(), 0);
}

TEST(StringInterface, CopyConstructortest) {
    String o("rong");
    String copy(o);
    EXPECT_EQ(copy.size(), 4);
    EXPECT_EQ(copy[0], 'r');
    EXPECT_EQ(copy[1], 'o');
    EXPECT_EQ(copy[2], 'n');
    EXPECT_EQ(copy[3], 'g');
    copy[0] = 'b';
    EXPECT_EQ(o[0], 'c');
    EXPECT_EQ(copy[0], 'b');
}

TEST(StringInterface, Assignmenttest) {
    String s("cat");
    String d("elephant");
    EXPECT_EQ(&(d = s), &d);
    EXPECT_EQ(d.size(), 3);
    EXPECT_EQ(d[0], 'c');
    EXPECT_EQ(d[1], 'a');
    EXPECT_EQ(d[2], 't');
    d[0] = 'b';
    EXPECT_EQ(s[0], 'c');
    String empty;
    d = empty;
    EXPECT_EQ(d.size(), 0);
}
