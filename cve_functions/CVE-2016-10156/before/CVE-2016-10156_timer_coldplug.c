static int timer_coldplug(Unit *u) {
        Timer *t = TIMER(u);

        assert(t);
        assert(t->state == TIMER_DEAD);

        if (t->deserialized_state != t->state) {

                if (t->deserialized_state == TIMER_WAITING)
                        timer_enter_waiting(t, false);
                else
                        timer_set_state(t, t->deserialized_state);
        }

        return 0;
}
