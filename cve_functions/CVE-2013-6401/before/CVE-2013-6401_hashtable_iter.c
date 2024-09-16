void *hashtable_iter(hashtable_t *hashtable)
{
    return hashtable_iter_next(hashtable, &hashtable->list);
}
