static int timer_stop(Unit *u) {
        Timer *t = TIMER(u);

        assert(t);
        assert(t->state == TIMER_WAITING || t->state == TIMER_RUNNING || t->state == TIMER_ELAPSED);

        timer_enter_dead(t, TIMER_SUCCESS);
        return 1;
}
