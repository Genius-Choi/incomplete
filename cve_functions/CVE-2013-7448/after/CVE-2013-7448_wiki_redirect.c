wiki_redirect(HttpResponse *res, char *location)
{
  int   header_len = strlen(location) + 14; 
  char *header = alloca(sizeof(char)*header_len);

  snprintf(header, header_len, "Location: %s\r\n", location);

  http_response_append_header(res, header);
  http_response_printf(res, "<html>\n<p>Redirect to %s</p>\n</html>\n", 
		       location);
  http_response_set_status(res, 302, "Moved Temporarily");
  http_response_send(res);

  exit(0);
}
