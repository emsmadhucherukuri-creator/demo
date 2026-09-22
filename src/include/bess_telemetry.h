#ifndef BESS_TELEMETRY_H
#define BESS_TELEMETRY_H

#include "bess_types.h"

#define BESS_TELEMETRY_HISTORY 256

typedef struct { bess_telemetry_t samples[BESS_TELEMETRY_HISTORY]; size_t count; size_t next; } bess_telemetry_store_t;

void bess_telemetry_init(bess_telemetry_store_t *store);
bess_status_t bess_telemetry_record(bess_telemetry_store_t *store, const bess_telemetry_t *sample);
bess_status_t bess_telemetry_latest(const bess_telemetry_store_t *store, bess_telemetry_t *sample);
bess_status_t bess_telemetry_export_csv(const bess_telemetry_store_t *store, const char *path);

#endif
