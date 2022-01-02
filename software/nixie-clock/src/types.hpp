#ifndef NIXIE_CLOCK_TYPES_HPP
#define NIXIE_CLOCK_TYPES_HPP

typedef struct {
    const char *zone;
    const char *ntpServer;
    int8_t tzoff;
} Timezone_t;

#endif //NIXIE_CLOCK_TYPES_HPP
