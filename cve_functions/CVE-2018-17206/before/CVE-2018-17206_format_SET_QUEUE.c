format_SET_QUEUE(const struct ofpact_queue *a, struct ds *s)
{
    ds_put_format(s, "%sset_queue:%s%"PRIu32,
                  colors.param, colors.end, a->queue_id);
}
