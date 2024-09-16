inline static const int16_t *get_line(const int16_t *ptr, uintptr_t offs, uintptr_t size)
{
    return offs < size ? ptr + offs : zero_line;
}
