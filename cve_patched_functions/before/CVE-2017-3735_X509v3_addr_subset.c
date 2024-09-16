int X509v3_addr_subset(IPAddrBlocks *a, IPAddrBlocks *b)
{
    int i;
    if (a == NULL || a == b)
        return 1;
    if (b == NULL || X509v3_addr_inherits(a) || X509v3_addr_inherits(b))
        return 0;
    (void)sk_IPAddressFamily_set_cmp_func(b, IPAddressFamily_cmp);
    for (i = 0; i < sk_IPAddressFamily_num(a); i++) {
        IPAddressFamily *fa = sk_IPAddressFamily_value(a, i);
        int j = sk_IPAddressFamily_find(b, fa);
        IPAddressFamily *fb;
        fb = sk_IPAddressFamily_value(b, j);
        if (fb == NULL)
            return 0;
        if (!addr_contains(fb->ipAddressChoice->u.addressesOrRanges,
                           fa->ipAddressChoice->u.addressesOrRanges,
                           length_from_afi(X509v3_addr_get_afi(fb))))
            return 0;
    }
    return 1;
}
