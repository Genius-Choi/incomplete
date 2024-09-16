static void send_ascii_command(const char *buf) {
    off_t offset = 0;
    const char* ptr = buf;
    size_t len = strlen(buf);

    do {
        ssize_t nw = write(sock, ptr + offset, len - offset);
        if (nw == -1) {
            if (errno != EINTR) {
                fprintf(stderr, "Failed to write: %s\n", strerror(errno));
                abort();
            }
        } else {
            offset += nw;
        }
    } while (offset < len);
}
