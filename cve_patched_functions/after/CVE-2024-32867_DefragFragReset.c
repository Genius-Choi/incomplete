DefragFragReset(Frag *frag)
{
    if (frag->pkt != NULL)
        SCFree(frag->pkt);
    memset(frag, 0, sizeof(*frag));
}
