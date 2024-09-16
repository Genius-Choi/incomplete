static int timer_deserialize_item(Unit *u, const char *key, const char *value, FDSet *fds) {
        Timer *t = TIMER(u);
        int r;

        assert(u);
        assert(key);
        assert(value);
        assert(fds);

        if (streq(key, "state")) {
                TimerState state;

                state = timer_state_from_string(value);
                if (state < 0)
                        log_unit_debug(u, "Failed to parse state value: %s", value);
                else
                        t->deserialized_state = state;
        } else if (streq(key, "result")) {
                TimerResult f;

                f = timer_result_from_string(value);
                if (f < 0)
                        log_unit_debug(u, "Failed to parse result value: %s", value);
                else if (f != TIMER_SUCCESS)
                        t->result = f;
        } else if (streq(key, "last-trigger-realtime")) {

                r = safe_atou64(value, &t->last_trigger.realtime);
                if (r < 0)
                        log_unit_debug(u, "Failed to parse last-trigger-realtime value: %s", value);

        } else if (streq(key, "last-trigger-monotonic")) {

                r = safe_atou64(value, &t->last_trigger.monotonic);
                if (r < 0)
                        log_unit_debug(u, "Failed to parse last-trigger-monotonic value: %s", value);

        } else
                log_unit_debug(u, "Unknown serialization key: %s", key);

        return 0;
}
