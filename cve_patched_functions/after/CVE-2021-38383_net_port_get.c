net_port_get(short unsigned *port, union net_sockaddr *naddr)
{
  if (naddr->sa.sa_family == AF_INET6)
     *port = ntohs(naddr->sin6.sin6_port);
  else
     *port = ntohs(naddr->sin.sin_port);

  return 0;
}
