void timer_free_values(Timer *t) {
        TimerValue *v;

        assert(t);

        while ((v = t->values)) {
                LIST_REMOVE(value, t->values, v);
                calendar_spec_free(v->calendar_spec);
                free(v);
        }
}
