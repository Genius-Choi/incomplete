static enum test_return stop_memcached_server(void) {
    close(sock);
    assert(kill(server_pid, SIGTERM) == 0);
    return TEST_PASS;
}
