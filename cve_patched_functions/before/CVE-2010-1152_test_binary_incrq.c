static enum test_return test_binary_incrq(void) {
    return test_binary_incr_impl("test_binary_incrq",
                                 PROTOCOL_BINARY_CMD_INCREMENTQ);
}
