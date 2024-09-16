static int timer_dispatch(sd_event_source *s, uint64_t usec, void *userdata) {
        Timer *t = TIMER(userdata);

        assert(t);

        if (t->state != TIMER_WAITING)
                return 0;

        log_unit_debug(UNIT(t), "Timer elapsed.");
        timer_enter_running(t);
        return 0;
}
