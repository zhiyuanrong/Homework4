#include <gtest/gtest.h>

#include <sstream>
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
    testing::internal::CaptureStderr();
    String word(long_input.c_str());
    const std::string error = testing::internal::GetCapturedStderr();

    EXPECT_EQ(word.size(), MAXLEN - 1);
    EXPECT_EQ(word[MAXLEN - 2], 'x');
    EXPECT_EQ(error, "ERROR: String Capacity Exceeded.\n");
}

TEST(StringInterface, SubscriptRejectsIndicesOutsideLogicalLength) {
    String word("cat");

    testing::internal::CaptureStderr();
    EXPECT_EQ(word[-1], 'c');
    EXPECT_EQ(word[word.size()], 'c');
    const std::string errors = testing::internal::GetCapturedStderr();

    EXPECT_EQ(errors,
              "ERROR: Index Out Of Bounds\n"
              "ERROR: Index Out Of Bounds\n");
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

TEST(StringInterface, IndexOfFindsCharactersAndStrings) {
    String text("hello world");

    EXPECT_EQ(text.indexOf('o'), 4);
    EXPECT_EQ(text.indexOf('x'), -1);
    EXPECT_EQ(text.indexOf(String("world")), 6);
    EXPECT_EQ(text.indexOf(String("cat")), -1);
}

TEST(StringInterface, ComparisonOperatorsCompareStrings) {
    String apple("apple");
    String another_apple("apple");
    String banana("banana");

    EXPECT_TRUE(apple == another_apple);
    EXPECT_FALSE(apple != another_apple);
    EXPECT_TRUE(apple < banana);
    EXPECT_TRUE(banana > apple);
    EXPECT_TRUE(apple <= another_apple);
    EXPECT_TRUE(apple >= another_apple);
}

TEST(StringInterface, PlusCreatesANewString) {
    String first("hello");
    String second(" world");
    String result = first + second;

    EXPECT_TRUE(result == String("hello world"));
    EXPECT_TRUE(first == String("hello"));
    EXPECT_TRUE(second == String(" world"));
}

TEST(StringInterface, PlusEqualsChangesTheCurrentString) {
    String word("go");
    word += String("od");
    EXPECT_TRUE(word == String("good"));

    String repeat("go");
    repeat += repeat;
    EXPECT_TRUE(repeat == String("gogo"));
}

TEST(StringInterface, ConcatenationReportsAndTruncatesAtCapacity) {
    std::string almost_full(MAXLEN - 2, 'a');
    String left(almost_full.c_str());
    String right("bc");

    testing::internal::CaptureStderr();
    left += right;
    const std::string error = testing::internal::GetCapturedStderr();

    EXPECT_EQ(error, "ERROR: String Capacity Exceeded.\n");
    EXPECT_EQ(left.size(), MAXLEN - 1);
    EXPECT_EQ(left[MAXLEN - 2], 'b');
}

TEST(StringInterface, PrintAndOutputOperatorWriteTheString) {
    String word("hello");

    std::ostringstream print_output;
    word.print(print_output);
    EXPECT_EQ(print_output.str(), "hello");

    std::ostringstream operator_output;
    operator_output << word;
    EXPECT_EQ(operator_output.str(), "hello");
}

TEST(StringInterface, ReadAndInputOperatorReadOneWord) {
    String first;
    std::istringstream first_input("cat dog");
    first.read(first_input);
    EXPECT_TRUE(first == String("cat"));

    String second;
    std::istringstream second_input("bird fish");
    second_input >> second;
    EXPECT_TRUE(second == String("bird"));
}

TEST(StringFunction, strlen) {
    EXPECT_EQ(String::strlen(""), 0);
    EXPECT_EQ(String::strlen("a"), 1);
    EXPECT_EQ(String::strlen("hello world"), 11);
}

TEST(StringFunction, strcpy) {
    char result[20];
    EXPECT_EQ(String::strcpy(result, "foo"), result);
    EXPECT_STREQ(result, "foo");
    EXPECT_EQ(String::strcpy(result, ""), result);
    EXPECT_STREQ(result, "");
}

TEST(StringFunction, strncpy) {
    char result[20];
    EXPECT_EQ(String::strncpy(result, "abcdef", 3), result);
    EXPECT_STREQ(result, "abc");
    String::strncpy(result, "cat", 10);
    EXPECT_STREQ(result, "cat");
    String::strncpy(result, "cat", 0);
    EXPECT_STREQ(result, "");
}

TEST(StringFunction, strcat) {
    char result[20] = "hello";
    EXPECT_EQ(String::strcat(result, " world"), result);
    EXPECT_STREQ(result, "hello world");
    String::strcat(result, "");
    EXPECT_STREQ(result, "hello world");
}

TEST(StringFunction, strncat) {
    char result[20] = "abc";
    EXPECT_EQ(String::strncat(result, "defghi", 3), result);
    EXPECT_STREQ(result, "abcdef");
    String::strncat(result, "xyz", 0);
    EXPECT_STREQ(result, "abcdef");
    String::strncat(result, "!", 5);
    EXPECT_STREQ(result, "abcdef!");
}

TEST(StringFunction, strcmp) {
    EXPECT_EQ(String::strcmp("same", "same"), 0);
    EXPECT_LT(String::strcmp("apple", "banana"), 0);
    EXPECT_GT(String::strcmp("banana", "apple"), 0);
    EXPECT_LT(String::strcmp("app", "apple"), 0);
    EXPECT_GT(String::strcmp("apple", "app"), 0);
}

TEST(StringFunction, strncmp) {
    EXPECT_EQ(String::strncmp("abc", "xyz", 0), 0);
    EXPECT_EQ(String::strncmp("abcdef", "abcxyz", 3), 0);
    EXPECT_LT(String::strncmp("abcdef", "abcxyz", 4), 0);
    EXPECT_GT(String::strncmp("abcxyz", "abcdef", 4), 0);
    EXPECT_EQ(String::strncmp("same", "same", 10), 0);
}

TEST(StringFunction, reverse_cpy) {
    char result[20];
    String::reverse_cpy(result, "abcd");
    EXPECT_STREQ(result, "dcba");
    String::reverse_cpy(result, "x");
    EXPECT_STREQ(result, "x");
    String::reverse_cpy(result, "");
    EXPECT_STREQ(result, "");
}

TEST(StringFunction, strchr) {
    const char text[] = "banana";
    EXPECT_EQ(String::strchr(text, 'b'), text);
    EXPECT_EQ(String::strchr(text, 'a'), text + 1);
    EXPECT_EQ(String::strchr(text, '\0'), text + 6);
    EXPECT_EQ(String::strchr(text, 'z'), nullptr);
}

TEST(StringFunction, strstr) {
    const char text[] = "one two three";
    const char repeated[] = "aaaab";
    EXPECT_EQ(String::strstr(text, "one"), text);
    EXPECT_EQ(String::strstr(text, "two"), text + 4);
    EXPECT_EQ(String::strstr(text, ""), text);
    EXPECT_EQ(String::strstr(text, "four"), nullptr);
    EXPECT_EQ(String::strstr(repeated, "aab"), repeated + 2);
}
