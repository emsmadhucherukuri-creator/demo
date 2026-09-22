#include "bess_alarm.h"
#include <string.h>

void bess_alarm_store_init(bess_alarm_store_t *store) { if (store != NULL) memset(store, 0, sizeof *store); }

bess_status_t bess_alarm_raise(bess_alarm_store_t *s, uint32_t id, bess_severity_t severity, const char *message, time_t now) {
    if (s == NULL || message == NULL || severity > BESS_EMERGENCY) return BESS_ERR_INVALID;
    for (size_t i = 0; i < s->count; ++i) if (s->items[i].id == id) { s->items[i].active = true; s->items[i].severity = severity; return BESS_OK; }
    if (s->count >= BESS_MAX_ALARMS) return BESS_ERR_FULL;
    bess_alarm_t *a = &s->items[s->count++]; a->id = id; a->severity = severity; a->active = true; a->raised_at = now;
    (void)snprintf(a->message, sizeof a->message, "%s", message);
    return BESS_OK;
}

bess_status_t bess_alarm_acknowledge(bess_alarm_store_t *s, uint32_t id) { if (s == NULL) return BESS_ERR_INVALID; for (size_t i=0;i<s->count;++i) if(s->items[i].id==id){s->items[i].acknowledged=true;return BESS_OK;} return BESS_ERR_INVALID; }
bess_status_t bess_alarm_clear(bess_alarm_store_t *s, uint32_t id) { if (s == NULL) return BESS_ERR_INVALID; for (size_t i=0;i<s->count;++i) if(s->items[i].id==id){s->items[i].active=false;return BESS_OK;} return BESS_ERR_INVALID; }
size_t bess_alarm_active_count(const bess_alarm_store_t *s) { size_t n=0; if(s!=NULL) for(size_t i=0;i<s->count;++i) n += s->items[i].active ? 1U : 0U; return n; }
