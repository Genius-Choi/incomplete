static bool safe_recv_packet(void *buf, size_t size) {
    protocol_binary_response_no_extras *response = buf;
    assert(size > sizeof(*response));
    if (!safe_recv(response, sizeof(*response))) {
        return false;
    }
    response->message.header.response.keylen = ntohs(response->message.header.response.keylen);
    response->message.header.response.status = ntohs(response->message.header.response.status);
    response->message.header.response.bodylen = ntohl(response->message.header.response.bodylen);

    size_t len = sizeof(*response);

    char *ptr = buf;
    ptr += len;
    if (!safe_recv(ptr, response->message.header.response.bodylen)) {
        return false;
    }

#ifdef MESSAGE_DEBUG
    usleep(500);
    ptr = buf;
    len += response->message.header.response.bodylen;
    uint8_t val = *ptr;
    assert(val == (uint8_t)0x81);
    fprintf(stderr, "Received %lu bytes:", (unsigned long)len);
    for (int ii = 0; ii < len; ++ii) {
        if (ii % 4 == 0) {
            fprintf(stderr, "\n   ");
        }
        val = *(ptr + ii);
        fprintf(stderr, " 0x%02x", val);
    }
    fprintf(stderr, "\n");
#endif
    return true;
}
