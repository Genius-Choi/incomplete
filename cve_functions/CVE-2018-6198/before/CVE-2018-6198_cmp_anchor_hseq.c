cmp_anchor_hseq(const void *a, const void *b)
{
    return (*((const Anchor **) a))->hseq - (*((const Anchor **) b))->hseq;
}
