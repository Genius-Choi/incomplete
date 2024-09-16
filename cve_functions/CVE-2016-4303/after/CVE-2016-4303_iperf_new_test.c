iperf_new_test()
{
    struct iperf_test *test;

    test = (struct iperf_test *) malloc(sizeof(struct iperf_test));
    if (!test) {
        i_errno = IENEWTEST;
        return NULL;
    }
    /* initialize everything to zero */
    memset(test, 0, sizeof(struct iperf_test));

    test->settings = (struct iperf_settings *) malloc(sizeof(struct iperf_settings));
    if (!test->settings) {
        free(test);
	i_errno = IENEWTEST;
	return NULL;
    }
    memset(test->settings, 0, sizeof(struct iperf_settings));

    return test;
}
