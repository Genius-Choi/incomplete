static void timer_done(Unit *u) {
        Timer *t = TIMER(u);

        assert(t);

        timer_free_values(t);

        t->monotonic_event_source = sd_event_source_unref(t->monotonic_event_source);
        t->realtime_event_source = sd_event_source_unref(t->realtime_event_source);

        free(t->stamp_path);
}
