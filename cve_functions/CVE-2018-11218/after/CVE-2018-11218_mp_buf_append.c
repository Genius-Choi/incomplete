void mp_buf_append(lua_State *L, mp_buf *buf, const unsigned char *s, size_t len) {
    if (buf->free < len) {
        size_t newsize = (buf->len+len)*2;

        buf->b = (unsigned char*)mp_realloc(L, buf->b, buf->len + buf->free, newsize);
        buf->free = newsize - buf->len;
    }
    memcpy(buf->b+buf->len,s,len);
    buf->len += len;
    buf->free -= len;
}
