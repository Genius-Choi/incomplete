bool tty_is_vc_resolve(const char *tty) {
        _cleanup_free_ char *resolved = NULL;

        assert(tty);

        tty = skip_dev_prefix(tty);

        if (streq(tty, "console")) {
                if (resolve_dev_console(&resolved) < 0)
                        return false;

                tty = resolved;
        }

        return tty_is_vc(tty);
}
