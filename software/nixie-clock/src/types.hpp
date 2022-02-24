#ifndef NIXIE_CLOCK_TYPES_HPP
#define NIXIE_CLOCK_TYPES_HPP

typedef struct Timezone_t {
    const char *zone;
    const char *ntpServer;
    int8_t tzoff;
} Timezone_t;

typedef struct BinaryCodedDecimal_t {
    bool a = false;
    bool b = false;
    bool c = false;
    bool d = false;
} BinaryCodedDecimal_t;
typedef struct NixieValues {
    int nixie1 = 0;
    int nixie2 = 0;
    int nixie3 = 0;
    int nixie4 = 0;
    int nixie5 = 0;
    int nixie6 = 0;
} NixieValues;

enum PowerStatus {
    ON = true, OFF = false
};

#endif //NIXIE_CLOCK_TYPES_HPP
