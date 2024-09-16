static enum test_return test_binary_prepend(void) {
    return test_binary_concat_impl("test_binary_prepend",
                                   PROTOCOL_BINARY_CMD_PREPEND);
}
