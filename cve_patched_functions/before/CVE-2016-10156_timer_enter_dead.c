static void timer_enter_dead(Timer *t, TimerResult f) {
        assert(t);

        if (f != TIMER_SUCCESS)
                t->result = f;

        timer_set_state(t, t->result != TIMER_SUCCESS ? TIMER_FAILED : TIMER_DEAD);
}
