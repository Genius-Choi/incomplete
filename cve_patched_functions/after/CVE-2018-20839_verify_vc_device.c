static int verify_vc_device(int fd) {
        unsigned char data[] = {
                TIOCL_GETFGCONSOLE,
        };

        int r;

        r = ioctl(fd, TIOCLINUX, data);
        if (r < 0)
                return -errno;

        return r;
}
