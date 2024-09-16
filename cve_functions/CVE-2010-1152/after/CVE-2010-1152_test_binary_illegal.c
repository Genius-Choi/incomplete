static enum test_return test_binary_illegal(void) {
    uint8_t cmd = 0x23;
    while (cmd != 0x00) {
        union {
            protocol_binary_request_no_extras request;
            protocol_binary_response_no_extras response;
            char bytes[1024];
        } buffer;
        size_t len = raw_command(buffer.bytes, sizeof(buffer.bytes),
                                 cmd, NULL, 0, NULL, 0);
        safe_send(buffer.bytes, len, false);
        safe_recv_packet(buffer.bytes, sizeof(buffer.bytes));
        validate_response_header(&buffer.response, cmd,
                                 PROTOCOL_BINARY_RESPONSE_UNKNOWN_COMMAND);
        ++cmd;
    }

    return TEST_PASS;
}
