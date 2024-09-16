count_non_skipped_files (GList *list)
{
    guint count;
    GList *node;
    GFileInfo *info;

    count = 0;
    for (node = list; node != NULL; node = node->next)
    {
        info = node->data;
        if (!should_skip_file (NULL, info))
        {
            count += 1;
        }
    }
    return count;
}
