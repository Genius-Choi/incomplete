void *hashtable_iter_value(void *iter)
{
    pair_t *pair = list_to_pair((list_t *)iter);
    return pair->value;
}
