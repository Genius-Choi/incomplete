static enum test_return test_binary_decr(void) {
    return test_binary_decr_impl("test_binary_decr",
                                 PROTOCOL_BINARY_CMD_DECREMENT);
}
