void reset_terminal_feature_caches(void) {
        cached_columns = 0;
        cached_lines = 0;

        cached_colors_enabled = -1;
        cached_underline_enabled = -1;
        cached_on_tty = -1;
}
