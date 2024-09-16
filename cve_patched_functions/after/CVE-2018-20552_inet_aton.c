inet_aton(const char *name, struct in_addr *addr)
{
    in_addr_t a = inet_addr(name);
    addr->s_addr = a;
    return a != (in_addr_t)-1;
}
