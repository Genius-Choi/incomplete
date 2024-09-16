static enum test_return test_binary_decrq(void) {
    return test_binary_decr_impl("test_binary_decrq",
                                 PROTOCOL_BINARY_CMD_DECREMENTQ);
}
