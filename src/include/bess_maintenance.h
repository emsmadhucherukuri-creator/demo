#ifndef BESS_MAINTENANCE_H
#define BESS_MAINTENANCE_H

#include "bess_types.h"

typedef struct { uint64_t charge_cycles; double energy_throughput_kwh; uint32_t fault_count; time_t last_service; } bess_maintenance_t;
void bess_maintenance_init(bess_maintenance_t *record, time_t now);
void bess_maintenance_update(bess_maintenance_t *record, double power_kw, double interval_seconds, bool fault);
bool bess_maintenance_due(const bess_maintenance_t *record, time_t now, uint32_t service_days);

#endif
