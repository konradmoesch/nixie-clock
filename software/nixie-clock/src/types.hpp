#ifndef NIXIE_CLOCK_TYPES_HPP
#define NIXIE_CLOCK_TYPES_HPP

#include <functional>

typedef struct {
    const char *zone;
    const char *ntpServer;
    int8_t tzoff;
} Timezone_t;

typedef struct BinaryCodedDecimal {
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
} NixieValues_t;

enum PowerStatus {
    ON = true, OFF = false
};

class InformationProvider;
typedef struct {
    String name;
    int providerIndex;
    InformationProvider* provider;
} InformationProvider_t;

template <typename T>
struct Callback;

template <typename Ret, typename... Params>
struct Callback<Ret(Params...)> {
    template <typename... Args>
    static Ret callback(Args... args) {
        return func(args...);
    }
    static std::function<Ret(Params...)> func;
};

template <typename Ret, typename... Params>
std::function<Ret(Params...)> Callback<Ret(Params...)>::func;

#endif //NIXIE_CLOCK_TYPES_HPP
