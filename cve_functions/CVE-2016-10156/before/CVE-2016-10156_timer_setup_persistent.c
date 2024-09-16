static int timer_setup_persistent(Timer *t) {
        int r;

        assert(t);

        if (!t->persistent)
                return 0;

        if (UNIT(t)->manager->running_as == MANAGER_SYSTEM) {

                r = unit_require_mounts_for(UNIT(t), "/var/lib/systemd/timers");
                if (r < 0)
                        return r;

                t->stamp_path = strappend("/var/lib/systemd/timers/stamp-", UNIT(t)->id);
        } else {
                const char *e;

                e = getenv("XDG_DATA_HOME");
                if (e)
                        t->stamp_path = strjoin(e, "/systemd/timers/stamp-", UNIT(t)->id, NULL);
                else {

                        _cleanup_free_ char *h = NULL;

                        r = get_home_dir(&h);
                        if (r < 0)
                                return log_unit_error_errno(UNIT(t), r, "Failed to determine home directory: %m");

                        t->stamp_path = strjoin(h, "/.local/share/systemd/timers/stamp-", UNIT(t)->id, NULL);
                }
        }

        if (!t->stamp_path)
                return log_oom();

        return 0;
}
