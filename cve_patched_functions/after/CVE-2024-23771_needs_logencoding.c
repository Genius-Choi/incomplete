static int needs_logencoding(const unsigned char c) {
    return ((c <= 0x1F) || (c >= 0x7F) || (c == '"'));
}
