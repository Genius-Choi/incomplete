static enum test_return test_binary_version(void) {
    union {
        protocol_binary_request_no_extras request;
        protocol_binary_response_no_extras response;
        char bytes[1024];
    } buffer;

    size_t len = raw_command(buffer.bytes, sizeof(buffer.bytes),
                             PROTOCOL_BINARY_CMD_VERSION,
                             NULL, 0, NULL, 0);

    safe_send(buffer.bytes, len, false);
    safe_recv_packet(buffer.bytes, sizeof(buffer.bytes));
    validate_response_header(&buffer.response, PROTOCOL_BINARY_CMD_VERSION,
                             PROTOCOL_BINARY_RESPONSE_SUCCESS);

    return TEST_PASS;
}
