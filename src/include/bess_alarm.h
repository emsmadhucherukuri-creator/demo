#ifndef BESS_ALARM_H
#define BESS_ALARM_H

#include "bess_types.h"

#define BESS_MAX_ALARMS 64

typedef struct {
    uint32_t id;
    bess_severity_t severity;
    bool active;
    bool acknowledged;
    time_t raised_at;
    char message[96];
} bess_alarm_t;

typedef struct { bess_alarm_t items[BESS_MAX_ALARMS]; size_t count; } bess_alarm_store_t;

void bess_alarm_store_init(bess_alarm_store_t *store);
bess_status_t bess_alarm_raise(bess_alarm_store_t *store, uint32_t id, bess_severity_t severity, const char *message, time_t now);
bess_status_t bess_alarm_acknowledge(bess_alarm_store_t *store, uint32_t id);
bess_status_t bess_alarm_clear(bess_alarm_store_t *store, uint32_t id);
size_t bess_alarm_active_count(const bess_alarm_store_t *store);

#endif
