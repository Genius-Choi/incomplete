istr_set_new (void)
{
    return g_hash_table_new_full (istr_hash, istr_equal, g_free, NULL);
}
