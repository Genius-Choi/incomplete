static void read_ascii_response(char *buffer, size_t size) {
    off_t offset = 0;
    bool need_more = true;
    do {
        ssize_t nr = read(sock, buffer + offset, 1);
        if (nr == -1) {
            if (errno != EINTR) {
                fprintf(stderr, "Failed to read: %s\n", strerror(errno));
                abort();
            }
        } else {
            assert(nr == 1);
            if (buffer[offset] == '\n') {
                need_more = false;
                buffer[offset + 1] = '\0';
            }
            offset += nr;
            assert(offset + 1 < size);
        }
    } while (need_more);
}
