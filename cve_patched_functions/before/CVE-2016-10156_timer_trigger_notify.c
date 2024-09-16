static void timer_trigger_notify(Unit *u, Unit *other) {
        Timer *t = TIMER(u);
        TimerValue *v;

        assert(u);
        assert(other);

        if (other->load_state != UNIT_LOADED)
                return;

        /* Reenable all timers that depend on unit state */
        LIST_FOREACH(value, v, t->values)
                if (v->base == TIMER_UNIT_ACTIVE ||
                    v->base == TIMER_UNIT_INACTIVE)
                        v->disabled = false;

        switch (t->state) {

        case TIMER_WAITING:
        case TIMER_ELAPSED:

                /* Recalculate sleep time */
                timer_enter_waiting(t, false);
                break;

        case TIMER_RUNNING:

                if (UNIT_IS_INACTIVE_OR_FAILED(unit_active_state(other))) {
                        log_unit_debug(UNIT(t), "Got notified about unit deactivation.");
                        timer_enter_waiting(t, false);
                }
                break;

        case TIMER_DEAD:
        case TIMER_FAILED:
                break;

        default:
                assert_not_reached("Unknown timer state");
        }
}
