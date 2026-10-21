#include "string.hpp"
String::String(const char *s) {
    int i = 0;

    while (i < MAXLEN - 1 && s[i] != '\0') {
        buf[i] = s[i];
        ++i;
    }

    buf[i] = '\0';
}

String::String(const String &s){
    int i = 0;
    while (s.buf[i] != '\0') {
        buf[i] = s.buf[i];
        ++i;
    }

    buf[i] = '\0';
}
String &String::operator=(const String &s){
	if (this == &s) {
        	return *this;
    }

    int i = 0;
    while (s.buf[i] != '\0') {
        buf[i] = s.buf[i];
        ++i;
    }
    buf[i] = '\0';
    return *this;
}
