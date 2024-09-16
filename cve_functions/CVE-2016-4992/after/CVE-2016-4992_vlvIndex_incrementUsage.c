vlvIndex_incrementUsage(struct vlvIndex* p)
{
    if (NULL == p)
        return;
    p->vlv_uses++;
}
