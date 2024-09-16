ofputil_bucket_clone_data(const struct ofputil_bucket *bucket)
{
    struct ofputil_bucket *new;

    new = xmemdup(bucket, sizeof *bucket);
    new->ofpacts = xmemdup(bucket->ofpacts, bucket->ofpacts_len);

    return new;
}
