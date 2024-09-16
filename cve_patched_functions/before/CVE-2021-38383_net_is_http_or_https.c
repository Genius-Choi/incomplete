net_is_http_or_https(const char *url)
{
  return (strncasecmp(url, "http://", strlen("http://")) == 0 || strncasecmp(url, "https://", strlen("https://")) == 0);
}
