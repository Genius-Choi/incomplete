int X509v3_addr_inherits(IPAddrBlocks *addr)
{
    int i;
    if (addr == NULL)
        return 0;
    for (i = 0; i < sk_IPAddressFamily_num(addr); i++) {
        IPAddressFamily *f = sk_IPAddressFamily_value(addr, i);
        if (f->ipAddressChoice->type == IPAddressChoice_inherit)
            return 1;
    }
    return 0;
}
