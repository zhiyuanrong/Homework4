#include "string.hpp"

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

char &String::operator[](int index){
    return buf[index];
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