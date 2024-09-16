ofputil_bucket_list_front(const struct ovs_list *buckets)
{
    static struct ofputil_bucket *bucket;

    ASSIGN_CONTAINER(bucket, ovs_list_front(buckets), list_node);

    return bucket;
}
