static enum test_return test_binary_replace(void) {
    return test_binary_replace_impl("test_binary_replace",
                                    PROTOCOL_BINARY_CMD_REPLACE);
}
