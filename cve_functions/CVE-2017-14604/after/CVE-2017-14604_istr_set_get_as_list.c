istr_set_get_as_list (GHashTable *table)
{
    GList *list;

    list = NULL;
    g_hash_table_foreach (table, add_istr_to_list, &list);
    return list;
}
