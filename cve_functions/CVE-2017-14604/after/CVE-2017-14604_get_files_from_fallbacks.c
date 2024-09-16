get_files_from_fallbacks (GList *fallbacks)
{
    MoveFileCopyFallback *fallback;
    GList *res, *l;

    res = NULL;
    for (l = fallbacks; l != NULL; l = l->next)
    {
        fallback = l->data;
        res = g_list_prepend (res, fallback->file);
    }
    return g_list_reverse (res);
}
