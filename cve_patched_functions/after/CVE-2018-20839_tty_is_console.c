bool tty_is_console(const char *tty) {
        assert(tty);

        return streq(skip_dev_prefix(tty), "console");
}
