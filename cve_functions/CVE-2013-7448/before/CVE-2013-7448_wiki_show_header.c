wiki_show_header(HttpResponse *res, char *page_title, int want_edit)
{
  http_response_printf(res, 
                       "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n"
                       "<html xmlns='http://www.w3.org/1999/xhtml'>\n"
		       "<head>\n"
                       "<meta http-equiv='Content-Type' content='text/html; charset=utf-8' />\n" 
		       "<link rel='SHORTCUT ICON' href='favicon.ico' />\n"
		       "<link media='all' href='styles.css' rel='stylesheet' type='text/css' />\n"
		       "<title>%s</title>\n"

		       "</head>\n"
		       "<body>\n", page_title
		       );

  http_response_printf(res, PAGEHEADER, page_title, 
		       (want_edit) ? " ( <a href='?edit' title='Edit this wiki page contents. [alt-j]' accesskey='j'>Edit</a> ) " : "" );     
}
