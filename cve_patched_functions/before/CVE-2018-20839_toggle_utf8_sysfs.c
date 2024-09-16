static int toggle_utf8_sysfs(bool utf8) {
        int r;

        r = write_string_file("/sys/module/vt/parameters/default_utf8", one_zero(utf8), WRITE_STRING_FILE_DISABLE_BUFFER);
        if (r < 0)
                return log_warning_errno(r, "Failed to %s sysfs UTF-8 flag: %m", enable_disable(utf8));

        log_debug("Sysfs UTF-8 flag %sd", enable_disable(utf8));
        return 0;
}
