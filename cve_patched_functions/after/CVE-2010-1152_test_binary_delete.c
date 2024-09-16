static enum test_return test_binary_delete(void) {
    return test_binary_delete_impl("test_binary_delete",
                                   PROTOCOL_BINARY_CMD_DELETE);
}
