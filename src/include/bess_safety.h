#ifndef BESS_SAFETY_H
#define BESS_SAFETY_H

#include "bess_types.h"

bess_limits_t bess_default_limits(void);
bess_status_t bess_validate_telemetry(const bess_telemetry_t *telemetry, const bess_limits_t *limits,
                                      const bess_health_t *health, char *reason, size_t reason_size);
bess_status_t bess_safe_power_command(double requested_kw, const bess_telemetry_t *telemetry,
                                      const bess_limits_t *limits, const bess_health_t *health,
                                      double *approved_kw);

#endif
