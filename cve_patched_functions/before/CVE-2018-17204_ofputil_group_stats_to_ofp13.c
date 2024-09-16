ofputil_group_stats_to_ofp13(const struct ofputil_group_stats *gs,
                             struct ofp13_group_stats *gs13, size_t length,
                             struct ofp11_bucket_counter bucket_cnts[])
{
    ofputil_group_stats_to_ofp11(gs, &gs13->gs, length, bucket_cnts);
    gs13->duration_sec = htonl(gs->duration_sec);
    gs13->duration_nsec = htonl(gs->duration_nsec);

}
