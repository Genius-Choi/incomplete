ofproto_set_dp_desc(struct ofproto *p, const char *dp_desc)
{
    free(p->dp_desc);
    p->dp_desc = nullable_xstrdup(dp_desc);
}
