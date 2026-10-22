#include "string.hpp"

#include <iostream>

char *String::strncpy(char *dest, const char *src, int n) {
    int i = 0;

    while (src[i] != '\0' && i < n) {
        dest[i] = src[i];
        ++i;
    }

    dest[i] = '\0';
    return dest;
}

String::String(const char *s) {
    if (strlen(s) >= MAXLEN) {
        std::cerr << "ERROR: String Capacity Exceeded." << std::endl;
    }
    strncpy(buf, s, MAXLEN - 1);
}


char *String::strcpy(char *dest, const char *src) {
    int i = 0;

    while (src[i] != '\0') {
        dest[i] = src[i];
        ++i;
    }

    dest[i] = '\0';
    return dest;
}

String::String(const String &s) {
    strcpy(buf, s.buf);
}

String &String::operator=(const String &s) {
    if (this != &s) {
        strcpy(buf, s.buf);
    }

    return *this;
}

char &String::operator[](int index) {
    if (!in_bounds(index)) {
        std::cerr << "ERROR: Index Out Of Bounds" << std::endl;
        return buf[0];
    }

    return buf[index];
}

bool String::in_bounds(int i) const {
    return i >= 0 && i < size();
}

int String::strlen(const char *s) {
    int length = 0;

    while (s[length] != '\0') {
        ++length;
    }

    return length;
}

int String::size() const{
    return strlen(buf);
}

void String::reverse_cpy(char *dest, const char *src) {
    int length = strlen(src);

    for (int i = 0; i < length; ++i) {
        dest[i] = src[length - 1 - i];
    }

    dest[length] = '\0';
}

String String::reverse() const{
    String result;
    reverse_cpy(result.buf, buf);
    return result;
}

const char *String::strchr(const char *str, char c) {
    int i = 0;

    while (true) {
        if (str[i] == c) {
            return &str[i];
        }
        if (str[i] == '\0') {
            return nullptr;
        }
        ++i;
    }
}

const char *String::strstr(const char *haystack, const char *needle) {
    if (needle[0] == '\0') {
        return haystack;
    }

    for (int i = 0; haystack[i] != '\0'; ++i) {
        int j = 0;

        while (
            needle[j] != '\0' &&
            haystack[i + j] != '\0' &&
            haystack[i + j] == needle[j]
        ) {
            ++j;
        }

        if (needle[j] == '\0') {
            return &haystack[i];
        }
    }

    return nullptr;
}


int String::indexOf(char c) const {
    const char *found = strchr(buf, c);

    if (found == nullptr) {
        return -1;
    }

    return static_cast<int>(found - buf);
}

int String::indexOf(const String &s) const {
    const char *found = strstr(buf, s.buf);

    if (found == nullptr) {
        return -1;
    }

    return static_cast<int>(found - buf);
}

char *String::strcat(char *dest, const char *src) {
    strcpy(dest + strlen(dest), src);
    return dest;
}

char *String::strncat(char *dest, const char *src, int n) {
    strncpy(dest + strlen(dest), src, n);
    return dest;
}

int String::strcmp(const char *left, const char *right) {
    int i = 0;

    while (left[i] != '\0' && left[i] == right[i]) {
        ++i;
    }

    return static_cast<unsigned char>(left[i])
        - static_cast<unsigned char>(right[i]);
}

int String::strncmp(const char *left, const char *right, int n) {
    int i = 0;

    while (i < n && left[i] != '\0' && left[i] == right[i]) {
        ++i;
    }

    if (i == n) {
        return 0;
    }

    return static_cast<unsigned char>(left[i])
        - static_cast<unsigned char>(right[i]);
}

bool String::operator==(const String &s) const {
    return strcmp(buf, s.buf) == 0;
}

bool String::operator!=(const String &s) const {
    return strcmp(buf, s.buf) != 0;
}

bool String::operator<(const String &s) const {
    return strcmp(buf, s.buf) < 0;
}

bool String::operator>(const String &s) const {
    return strcmp(buf, s.buf) > 0;
}

bool String::operator<=(const String &s) const {
    return strcmp(buf, s.buf) <= 0;
}

bool String::operator>=(const String &s) const {
    return strcmp(buf, s.buf) >= 0;
}
 
String String::operator+(const String &s) const {
    String result = *this;
    result += s;
    return result;
}

String &String::operator+=(const String &s) {
    int remaining = MAXLEN - size() - 1;

    if (s.size() > remaining) {
        std::cerr << "ERROR: String Capacity Exceeded." << std::endl;
    }

    if (this == &s) {
        String copy(s);
        strncat(buf, copy.buf, remaining);
    } else {
        strncat(buf, s.buf, remaining);
    }

    return *this;
}

void String::print(std::ostream &out) const {
    out << buf;
}

void String::read(std::istream &in) {
    in.width(MAXLEN);
    in >> buf;
}

String::~String() {
}

std::ostream &operator<<(std::ostream &out, const String &s) {
    s.print(out);
    return out;
}

std::istream &operator>>(std::istream &in, String &s) {
    s.read(in);
    return in;
}
