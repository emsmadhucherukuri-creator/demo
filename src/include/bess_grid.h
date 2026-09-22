#ifndef BESS_GRID_H
#define BESS_GRID_H

#include "bess_types.h"

bess_status_t bess_grid_support_command(const bess_telemetry_t *telemetry, double nominal_frequency_hz,
                                        double nominal_voltage_v, double frequency_gain_kw_per_hz,
                                        double voltage_gain_kvar_per_v, const bess_limits_t *limits,
                                        const bess_health_t *health, double *active_kw, double *reactive_kvar);

#endif
