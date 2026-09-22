#include "bess_grid.h"
#include "bess_safety.h"
#include <math.h>

bess_status_t bess_grid_support_command(const bess_telemetry_t *t, double nominal_frequency, double nominal_voltage,
                                        double frequency_gain, double voltage_gain, const bess_limits_t *l,
                                        const bess_health_t *h, double *active, double *reactive) {
    if(t==NULL||l==NULL||h==NULL||active==NULL||reactive==NULL||!isfinite(nominal_frequency)||!isfinite(nominal_voltage))return BESS_ERR_INVALID;
    double p=(nominal_frequency-t->grid_frequency_hz)*frequency_gain; double q=(nominal_voltage-t->grid_voltage_v)*voltage_gain;
    double safe; bess_status_t status=bess_safe_power_command(p,t,l,h,&safe); *active=safe;
    if(q>l->max_discharge_kw)q=l->max_discharge_kw; if(q<-l->max_charge_kw)q=-l->max_charge_kw; *reactive=q; return status;
}
