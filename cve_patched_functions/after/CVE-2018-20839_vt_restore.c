int vt_restore(int fd) {
        static const struct vt_mode mode = {
                .mode = VT_AUTO,
        };
        int r, q = 0;

        r = ioctl(fd, KDSETMODE, KD_TEXT);
        if (r < 0)
                q = log_debug_errno(errno, "Failed to set VT in text mode, ignoring: %m");

        r = vt_reset_keyboard(fd);
        if (r < 0) {
                log_debug_errno(r, "Failed to reset keyboard mode, ignoring: %m");
                if (q >= 0)
                        q = r;
        }

        r = ioctl(fd, VT_SETMODE, &mode);
        if (r < 0) {
                log_debug_errno(errno, "Failed to set VT_AUTO mode, ignoring: %m");
                if (q >= 0)
                        q = -errno;
        }

        r = fchown(fd, 0, (gid_t) -1);
        if (r < 0) {
                log_debug_errno(errno, "Failed to chown VT, ignoring: %m");
                if (q >= 0)
                        q = -errno;
        }

        return q;
}
