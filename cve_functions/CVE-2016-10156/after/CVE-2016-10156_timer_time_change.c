static void timer_time_change(Unit *u) {
        Timer *t = TIMER(u);

        assert(u);

        if (t->state != TIMER_WAITING)
                return;

        log_unit_debug(u, "Time change, recalculating next elapse.");
        timer_enter_waiting(t, false);
}
