static enum test_return test_binary_setq(void) {
    return test_binary_set_impl("test_binary_setq", PROTOCOL_BINARY_CMD_SETQ);
}
