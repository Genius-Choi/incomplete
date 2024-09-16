static JSON_INLINE int bucket_is_empty(hashtable_t *hashtable, bucket_t *bucket)
{
    return bucket->first == &hashtable->list && bucket->first == bucket->last;
}
