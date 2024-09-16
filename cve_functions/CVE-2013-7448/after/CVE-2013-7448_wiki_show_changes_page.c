wiki_show_changes_page(HttpResponse *res)
{
  WikiPageList **pages = NULL;
  int            n_pages, i;

  wiki_show_header(res, "Changes", FALSE);

  pages = wiki_get_pages(&n_pages, NULL);

  for (i=0; i<n_pages; i++)
    {
      struct tm   *pTm;
      char   datebuf[64];

      pTm = localtime(&pages[i]->mtime);
      strftime(datebuf, sizeof(datebuf), "%Y-%m-%d %H:%M", pTm);
      http_response_printf(res, "<a href='%s'>%s</a> %s<br />\n", 
			   pages[i]->name, 
			   pages[i]->name, 
			   datebuf);
    }

  wiki_show_footer(res);
  http_response_send(res);
  exit(0);
}
