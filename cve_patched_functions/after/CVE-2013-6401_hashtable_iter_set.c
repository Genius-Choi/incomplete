void hashtable_iter_set(void *iter, json_t *value)
{
    pair_t *pair = list_to_pair((list_t *)iter);

    json_decref(pair->value);
    pair->value = value;
}
