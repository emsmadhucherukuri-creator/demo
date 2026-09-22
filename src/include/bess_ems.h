#ifndef BESS_EMS_H
#define BESS_EMS_H

#include "bess_types.h"

typedef struct { double import_tariff; double export_tariff; double target_peak_kw; bool backup_reserve; } bess_ems_config_t;
bess_status_t bess_ems_dispatch(const bess_ems_config_t *config, const bess_telemetry_t *telemetry,
                                const bess_limits_t *limits, const bess_health_t *health, double *power_kw);

#endif
