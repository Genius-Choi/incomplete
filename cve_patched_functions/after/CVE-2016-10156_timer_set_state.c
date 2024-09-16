static void timer_set_state(Timer *t, TimerState state) {
        TimerState old_state;
        assert(t);

        old_state = t->state;
        t->state = state;

        if (state != TIMER_WAITING) {
                t->monotonic_event_source = sd_event_source_unref(t->monotonic_event_source);
                t->realtime_event_source = sd_event_source_unref(t->realtime_event_source);
        }

        if (state != old_state)
                log_unit_debug(UNIT(t), "Changed %s -> %s", timer_state_to_string(old_state), timer_state_to_string(state));

        unit_notify(UNIT(t), state_translation_table[old_state], state_translation_table[state], true);
}
