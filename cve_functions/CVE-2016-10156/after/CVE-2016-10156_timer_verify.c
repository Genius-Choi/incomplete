static int timer_verify(Timer *t) {
        assert(t);

        if (UNIT(t)->load_state != UNIT_LOADED)
                return 0;

        if (!t->values) {
                log_unit_error(UNIT(t), "Timer unit lacks value setting. Refusing.");
                return -EINVAL;
        }

        return 0;
}
