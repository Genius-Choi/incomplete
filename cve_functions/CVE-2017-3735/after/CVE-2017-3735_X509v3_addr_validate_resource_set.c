int X509v3_addr_validate_resource_set(STACK_OF(X509) *chain,
                                  IPAddrBlocks *ext, int allow_inheritance)
{
    if (ext == NULL)
        return 1;
    if (chain == NULL || sk_X509_num(chain) == 0)
        return 0;
    if (!allow_inheritance && X509v3_addr_inherits(ext))
        return 0;
    return addr_validate_path_internal(NULL, chain, ext);
}
