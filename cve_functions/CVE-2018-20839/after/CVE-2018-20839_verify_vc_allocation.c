static int verify_vc_allocation(unsigned idx) {
        char vcname[sizeof("/dev/vcs") + DECIMAL_STR_MAX(unsigned) - 2];

        xsprintf(vcname, "/dev/vcs%u", idx);

        if (access(vcname, F_OK) < 0)
                return -errno;

        return 0;
}
