void mp_cur_init(mp_cur *cursor, const unsigned char *s, size_t len) {
    cursor->p = s;
    cursor->left = len;
    cursor->err = MP_CUR_ERROR_NONE;
}
