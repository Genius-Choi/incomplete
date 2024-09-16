static int timer_add_default_dependencies(Timer *t) {
        int r;
        TimerValue *v;

        assert(t);

        if (!UNIT(t)->default_dependencies)
                return 0;

        r = unit_add_dependency_by_name(UNIT(t), UNIT_BEFORE, SPECIAL_TIMERS_TARGET, NULL, true);
        if (r < 0)
                return r;

        if (UNIT(t)->manager->running_as == MANAGER_SYSTEM) {
                r = unit_add_two_dependencies_by_name(UNIT(t), UNIT_AFTER, UNIT_REQUIRES, SPECIAL_SYSINIT_TARGET, NULL, true);
                if (r < 0)
                        return r;

                LIST_FOREACH(value, v, t->values) {
                        if (v->base == TIMER_CALENDAR) {
                                r = unit_add_dependency_by_name(UNIT(t), UNIT_AFTER, SPECIAL_TIME_SYNC_TARGET, NULL, true);
                                if (r < 0)
                                        return r;
                                break;
                        }
                }
        }

        return unit_add_two_dependencies_by_name(UNIT(t), UNIT_BEFORE, UNIT_CONFLICTS, SPECIAL_SHUTDOWN_TARGET, NULL, true);
}
