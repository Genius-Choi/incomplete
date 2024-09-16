const char *default_term_for_tty(const char *tty) {
        return tty && tty_is_vc_resolve(tty) ? "linux" : "vt220";
}
