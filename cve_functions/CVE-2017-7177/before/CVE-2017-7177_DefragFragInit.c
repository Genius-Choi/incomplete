DefragFragInit(void *data, void *initdata)
{
    Frag *frag = data;

    memset(frag, 0, sizeof(*frag));
    return 1;
}
