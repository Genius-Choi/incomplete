ofproto_set_cpu_mask(const char *cmask)
{
    free(pmd_cpu_mask);
    pmd_cpu_mask = nullable_xstrdup(cmask);
}
