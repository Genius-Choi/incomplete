static void timer_dump(Unit *u, FILE *f, const char *prefix) {
        char buf[FORMAT_TIMESPAN_MAX];
        Timer *t = TIMER(u);
        Unit *trigger;
        TimerValue *v;

        trigger = UNIT_TRIGGER(u);

        fprintf(f,
                "%sTimer State: %s\n"
                "%sResult: %s\n"
                "%sUnit: %s\n"
                "%sPersistent: %s\n"
                "%sWakeSystem: %s\n"
                "%sAccuracy: %s\n",
                prefix, timer_state_to_string(t->state),
                prefix, timer_result_to_string(t->result),
                prefix, trigger ? trigger->id : "n/a",
                prefix, yes_no(t->persistent),
                prefix, yes_no(t->wake_system),
                prefix, format_timespan(buf, sizeof(buf), t->accuracy_usec, 1));

        LIST_FOREACH(value, v, t->values) {

                if (v->base == TIMER_CALENDAR) {
                        _cleanup_free_ char *p = NULL;

                        calendar_spec_to_string(v->calendar_spec, &p);

                        fprintf(f,
                                "%s%s: %s\n",
                                prefix,
                                timer_base_to_string(v->base),
                                strna(p));
                } else  {
                        char timespan1[FORMAT_TIMESPAN_MAX];

                        fprintf(f,
                                "%s%s: %s\n",
                                prefix,
                                timer_base_to_string(v->base),
                                format_timespan(timespan1, sizeof(timespan1), v->value, 0));
                }
        }
}
