check_port(uschar *address)
{
int port = host_address_extract_port(address);
if (string_is_ip_address(address, NULL) == 0)
  {
  fprintf(stderr, "exim abandoned: \"%s\" is not an IP address\n", address);
  exit(EXIT_FAILURE);
  }
return port;
}
