static enum test_return test_binary_flush_impl(const char *key, uint8_t cmd) {
    union {
        protocol_binary_request_no_extras request;
        protocol_binary_response_no_extras response;
        char bytes[1024];
    } send, receive;

    size_t len = storage_command(send.bytes, sizeof(send.bytes),
                                 PROTOCOL_BINARY_CMD_ADD,
                                 key, strlen(key), NULL, 0, 0, 0);
    safe_send(send.bytes, len, false);
    safe_recv_packet(receive.bytes, sizeof(receive.bytes));
    validate_response_header(&receive.response, PROTOCOL_BINARY_CMD_ADD,
                             PROTOCOL_BINARY_RESPONSE_SUCCESS);

    len = flush_command(send.bytes, sizeof(send.bytes), cmd, 2, true);
    safe_send(send.bytes, len, false);
    if (cmd == PROTOCOL_BINARY_CMD_FLUSH) {
        safe_recv_packet(receive.bytes, sizeof(receive.bytes));
        validate_response_header(&receive.response, cmd,
                                 PROTOCOL_BINARY_RESPONSE_SUCCESS);
    }

    len = raw_command(send.bytes, sizeof(send.bytes), PROTOCOL_BINARY_CMD_GET,
                      key, strlen(key), NULL, 0);
    safe_send(send.bytes, len, false);
    safe_recv_packet(receive.bytes, sizeof(receive.bytes));
    validate_response_header(&receive.response, PROTOCOL_BINARY_CMD_GET,
                             PROTOCOL_BINARY_RESPONSE_SUCCESS);

    sleep(2);
    safe_send(send.bytes, len, false);
    safe_recv_packet(receive.bytes, sizeof(receive.bytes));
    validate_response_header(&receive.response, PROTOCOL_BINARY_CMD_GET,
                             PROTOCOL_BINARY_RESPONSE_KEY_ENOENT);

    int ii;
    for (ii = 0; ii < 2; ++ii) {
        len = storage_command(send.bytes, sizeof(send.bytes),
                              PROTOCOL_BINARY_CMD_ADD,
                              key, strlen(key), NULL, 0, 0, 0);
        safe_send(send.bytes, len, false);
        safe_recv_packet(receive.bytes, sizeof(receive.bytes));
        validate_response_header(&receive.response, PROTOCOL_BINARY_CMD_ADD,
                                 PROTOCOL_BINARY_RESPONSE_SUCCESS);

        len = flush_command(send.bytes, sizeof(send.bytes), cmd, 0, ii == 0);
        safe_send(send.bytes, len, false);
        if (cmd == PROTOCOL_BINARY_CMD_FLUSH) {
            safe_recv_packet(receive.bytes, sizeof(receive.bytes));
            validate_response_header(&receive.response, cmd,
                                     PROTOCOL_BINARY_RESPONSE_SUCCESS);
        }

        len = raw_command(send.bytes, sizeof(send.bytes),
                          PROTOCOL_BINARY_CMD_GET,
                          key, strlen(key), NULL, 0);
        safe_send(send.bytes, len, false);
        safe_recv_packet(receive.bytes, sizeof(receive.bytes));
        validate_response_header(&receive.response, PROTOCOL_BINARY_CMD_GET,
                                 PROTOCOL_BINARY_RESPONSE_KEY_ENOENT);
    }

    return TEST_PASS;
}
