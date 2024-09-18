static char *list2lines(GList *list)
{
    struct strbuf *s = strbuf_new();
    while (list)
    {
        strbuf_append_str(s, (char*)list->data);
        strbuf_append_char(s, '\n');
        free(list->data);
        list = g_list_delete_link(list, list);
    }
    return strbuf_free_nobuf(s);
}
