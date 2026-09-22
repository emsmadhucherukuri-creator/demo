#ifndef BESS_TYPES_H
#define BESS_TYPES_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <time.h>

typedef enum {
    BESS_OK = 0,
    BESS_ERR_INVALID = -1,
    BESS_ERR_LIMIT = -2,
    BESS_ERR_STATE = -3,
    BESS_ERR_AUTH = -4,
    BESS_ERR_FULL = -5
} bess_status_t;

typedef enum {
    BESS_MODE_STANDBY,
    BESS_MODE_CHARGE,
    BESS_MODE_DISCHARGE,
    BESS_MODE_GRID_SUPPORT,
    BESS_MODE_PEAK_SHAVING,
    BESS_MODE_BACKUP,
    BESS_MODE_MAINTENANCE,
    BESS_MODE_EMERGENCY
} bess_mode_t;

typedef enum { BESS_INFO, BESS_WARNING, BESS_MAJOR, BESS_CRITICAL, BESS_EMERGENCY } bess_severity_t;
typedef enum { BESS_ROLE_VIEWER, BESS_ROLE_OPERATOR, BESS_ROLE_ENGINEER, BESS_ROLE_ADMIN } bess_role_t;

typedef struct {
    double voltage_v;
    double current_a;
    double temperature_c;
    double soc_pct;
    double soh_pct;
    double active_power_kw;
    double reactive_power_kvar;
    double site_load_kw;
    double renewable_kw;
    double grid_frequency_hz;
    double grid_voltage_v;
    time_t timestamp;
} bess_telemetry_t;

typedef struct {
    double min_voltage_v, max_voltage_v;
    double min_temperature_c, max_temperature_c;
    double max_charge_current_a, max_discharge_current_a;
    double min_soc_pct, max_soc_pct, reserve_soc_pct;
    double max_charge_kw, max_discharge_kw;
} bess_limits_t;

typedef struct {
    bool emergency_stop;
    bool communication_ok;
    bool thermal_ok;
    bool breaker_closed;
    bool bms_ok;
    bool pcs_ok;
} bess_health_t;

#endif
