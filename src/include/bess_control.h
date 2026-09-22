#ifndef BESS_CONTROL_H
#define BESS_CONTROL_H

#include "bess_types.h"

bess_status_t bess_set_mode(bess_mode_t requested, const bess_health_t *health, bess_mode_t *current);
bess_status_t bess_command_power(bess_mode_t mode, double requested_kw, const bess_telemetry_t *telemetry,
                                 const bess_limits_t *limits, const bess_health_t *health, double *approved_kw);
bool bess_mode_allows_power(bess_mode_t mode);

#endif
