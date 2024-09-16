static int keyboard_load_and_wait(const char *vc, const char *map, const char *map_toggle, bool utf8) {
        const char *args[8];
        unsigned i = 0;
        pid_t pid;
        int r;

        /* An empty map means kernel map */
        if (isempty(map))
                return 0;

        args[i++] = KBD_LOADKEYS;
        args[i++] = "-q";
        args[i++] = "-C";
        args[i++] = vc;
        if (utf8)
                args[i++] = "-u";
        args[i++] = map;
        if (map_toggle)
                args[i++] = map_toggle;
        args[i++] = NULL;

        if (DEBUG_LOGGING) {
                _cleanup_free_ char *cmd;

                cmd = strv_join((char**) args, " ");
                log_debug("Executing \"%s\"...", strnull(cmd));
        }

        r = safe_fork("(loadkeys)", FORK_RESET_SIGNALS|FORK_CLOSE_ALL_FDS|FORK_RLIMIT_NOFILE_SAFE|FORK_LOG, &pid);
        if (r < 0)
                return r;
        if (r == 0) {
                execv(args[0], (char **) args);
                _exit(EXIT_FAILURE);
        }

        return wait_for_terminate_and_check(KBD_LOADKEYS, pid, WAIT_LOG);
}
