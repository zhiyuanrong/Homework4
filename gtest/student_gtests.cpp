#include <gtest/gtest.h>

#include <string>

#include "string.hpp"


TEST(StringInterface, CStringConstructor) {
    String word("jasonrong");
    EXPECT_EQ(word.size(), 9);
    EXPECT_EQ(word[0], 'j');
    EXPECT_EQ(word[8], 'g');

    String empty;
    EXPECT_EQ(empty.size(), 0);
    EXPECT_EQ(empty[0], '\0');
}

TEST(StringInterface, CStringConstructorTruncatesLongInput) {
    std::string long_input(MAXLEN + 20, 'x');
    String word(long_input.c_str());

    EXPECT_EQ(word.size(), MAXLEN - 1);
    EXPECT_EQ(word[MAXLEN - 2], 'x');
    EXPECT_EQ(word[MAXLEN - 1], '\0');
}

TEST(StringInterface, CopyConstructorMakesIndependentCopy) {
    String original("rong");
    String copy(original);

    EXPECT_EQ(copy.size(), 4);
    EXPECT_EQ(copy[0], 'r');
    EXPECT_EQ(copy[3], 'g');

    copy[0] = 'b';
    EXPECT_EQ(original[0], 'r');
    EXPECT_EQ(copy[0], 'b');
}

TEST(StringInterface, AssignmentCopiesAndReturnsLeftOperand) {
    String source("cat");
    String destination("elephant");

    EXPECT_EQ(&(destination = source), &destination);
    EXPECT_EQ(destination.size(), 3);
    EXPECT_EQ(destination[0], 'c');
    EXPECT_EQ(destination[2], 't');

    destination[0] = 'b';
    EXPECT_EQ(source[0], 'c');
    EXPECT_EQ(destination[0], 'b');
}

TEST(StringInterface, AssignmentHandlesSelfAssignmentAndEmptyString) {
    String word("cat");

    word = word;
    EXPECT_EQ(word.size(), 3);
    EXPECT_EQ(word[0], 'c');
    EXPECT_EQ(word[2], 't');

    word = String();
    EXPECT_EQ(word.size(), 0);
    EXPECT_EQ(word[0], '\0');
}

TEST(StringInterface, SubscriptReadsAndWritesCharacters) {
    String word("cat");

    EXPECT_EQ(word[0], 'c');
    EXPECT_EQ(word[2], 't');

    word[1] = 'u';
    EXPECT_EQ(word[1], 'u');
}

TEST(StringInterface, SizeReportsLogicalLength) {
    EXPECT_EQ(String().size(), 0);
    EXPECT_EQ(String("a").size(), 1);
    EXPECT_EQ(String("hello").size(), 5);
}

TEST(StringInterface, ReverseReturnsNewReversedString) {
    String original("abcd");
    String reversed = original.reverse();

    EXPECT_EQ(reversed.size(), 4);
    EXPECT_EQ(reversed[0], 'd');
    EXPECT_EQ(reversed[1], 'c');
    EXPECT_EQ(reversed[2], 'b');
    EXPECT_EQ(reversed[3], 'a');

    // reverse() must not modify the original object.
    EXPECT_EQ(original[0], 'a');
    EXPECT_EQ(original[3], 'd');
}

TEST(StringInterface, ReverseHandlesEmptyAndSingleCharacterStrings) {
    String reversed_empty = String().reverse();
    EXPECT_EQ(reversed_empty.size(), 0);
    EXPECT_EQ(reversed_empty[0], '\0');

    String reversed_single = String("x").reverse();
    EXPECT_EQ(reversed_single.size(), 1);
    EXPECT_EQ(reversed_single[0], 'x');
}
