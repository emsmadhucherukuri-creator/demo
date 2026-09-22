#include <assert.h>
#include <stdio.h>
#include "bess_control.h"
#include "bess_alarm.h"
#include "bess_auth.h"

int main(void) {
    bess_limits_t limits=bess_default_limits();
    bess_health_t health={false,true,true,true,true,true};
    bess_telemetry_t telemetry={750.0,0.0,25.0,50.0,98.0,0.0,0.0,100.0,0.0,50.0,480.0,0};
    double approved=0.0;
    assert(bess_command_power(BESS_MODE_DISCHARGE,100.0,&telemetry,&limits,&health,&approved)==BESS_OK);
    assert(approved==100.0);
    bess_alarm_store_t alarms; bess_alarm_store_init(&alarms);
    assert(bess_alarm_raise(&alarms,1,BESS_WARNING,"test",0)==BESS_OK);
    assert(bess_alarm_active_count(&alarms)==1U);
    assert(bess_authorize(BESS_ROLE_VIEWER,false,false));
    assert(!bess_authorize(BESS_ROLE_VIEWER,true,false));
    puts("BESS unit checks passed"); return 0;
}
