sockaddr_inet(short family, inet_address_t *addr)
{
    SOCKADDR_INET sa_inet;
    ZeroMemory(&sa_inet, sizeof(sa_inet));
    sa_inet.si_family = family;
    if (family == AF_INET)
    {
        sa_inet.Ipv4.sin_addr = addr->ipv4;
    }
    else if (family == AF_INET6)
    {
        sa_inet.Ipv6.sin6_addr = addr->ipv6;
    }
    return sa_inet;
}
