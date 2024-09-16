wiki_show_edit_page(HttpResponse *res, char *wikitext, char *page)
{
  wiki_show_header(res, page, FALSE);

  if (wikitext == NULL) wikitext = "";
  http_response_printf(res, EDITFORM, page, wikitext);
		       
  wiki_show_footer(res);

  http_response_send(res);
  exit(0);
}
