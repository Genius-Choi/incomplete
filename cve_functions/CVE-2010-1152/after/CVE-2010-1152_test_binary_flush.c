static enum test_return test_binary_flush(void) {
    return test_binary_flush_impl("test_binary_flush",
                                  PROTOCOL_BINARY_CMD_FLUSH);
}
