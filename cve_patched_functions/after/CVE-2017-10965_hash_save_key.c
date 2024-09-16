void hash_save_key(char *key, void *value, GSList **list)
{
        *list = g_slist_append(*list, key);
}
