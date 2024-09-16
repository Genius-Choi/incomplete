_pure_ static const char *timer_sub_state_to_string(Unit *u) {
        assert(u);

        return timer_state_to_string(TIMER(u)->state);
}
