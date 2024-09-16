njs_lvlhsh_alloc(void *data, size_t size)
{
    return njs_mp_align(data, size, size);
}
