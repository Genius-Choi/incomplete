static enum test_return test_binary_prependq(void) {
    return test_binary_concat_impl("test_binary_prependq",
                                   PROTOCOL_BINARY_CMD_PREPENDQ);
}
