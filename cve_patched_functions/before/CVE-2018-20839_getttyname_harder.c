int getttyname_harder(int fd, char **ret) {
        _cleanup_free_ char *s = NULL;
        int r;

        r = getttyname_malloc(fd, &s);
        if (r < 0)
                return r;

        if (streq(s, "tty"))
                return get_ctty(0, NULL, ret);

        *ret = TAKE_PTR(s);
        return 0;
}
