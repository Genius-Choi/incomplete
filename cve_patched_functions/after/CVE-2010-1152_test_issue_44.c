static enum test_return test_issue_44(void) {
    in_port_t port;
    pid_t pid = start_server(&port, true, 15);
    assert(kill(pid, SIGHUP) == 0);
    sleep(1);
    assert(kill(pid, SIGTERM) == 0);

    return TEST_PASS;
}
