Strnew()
{
    Str x = GC_MALLOC(sizeof(struct _Str));
    x->ptr = GC_MALLOC_ATOMIC(INITIAL_STR_SIZE);
    x->ptr[0] = '\0';
    x->area_size = INITIAL_STR_SIZE;
    x->length = 0;
    return x;
}
