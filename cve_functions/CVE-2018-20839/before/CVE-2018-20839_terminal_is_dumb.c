bool terminal_is_dumb(void) {
        if (!on_tty())
                return true;

        return getenv_terminal_is_dumb();
}
