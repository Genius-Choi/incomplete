get_one_value (GHashTable *table)
{
    gpointer value;

    value = NULL;
    if (table != NULL)
    {
        g_hash_table_foreach (table, get_one_value_callback, &value);
    }
    return value;
}
