static void timer_reset_failed(Unit *u) {
        Timer *t = TIMER(u);

        assert(t);

        if (t->state == TIMER_FAILED)
                timer_set_state(t, TIMER_DEAD);

        t->result = TIMER_SUCCESS;
}
