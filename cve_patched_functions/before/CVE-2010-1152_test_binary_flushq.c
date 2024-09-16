static enum test_return test_binary_flushq(void) {
    return test_binary_flush_impl("test_binary_flushq",
                                  PROTOCOL_BINARY_CMD_FLUSHQ);
}
