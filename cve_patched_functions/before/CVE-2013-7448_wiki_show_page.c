wiki_show_page(HttpResponse *res, char *wikitext, char *page)
{
  char *html_clean_wikitext = NULL;

  http_response_printf_alloc_buffer(res, strlen(wikitext)*2);

  wiki_show_header(res, page, TRUE);

  html_clean_wikitext = util_htmlize(wikitext, strlen(wikitext));

  wiki_print_data_as_html(res, html_clean_wikitext);      

  wiki_show_footer(res);  

  http_response_send(res);

  exit(0);

}
