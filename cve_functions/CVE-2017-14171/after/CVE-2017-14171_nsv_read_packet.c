static int nsv_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    NSVContext *nsv = s->priv_data;
    int i, err = 0;

    /* in case we don't already have something to eat ... */
    if (!nsv->ahead[0].data && !nsv->ahead[1].data)
        err = nsv_read_chunk(s, 0);
    if (err < 0)
        return err;

    /* now pick one of the plates */
    for (i = 0; i < 2; i++) {
        if (nsv->ahead[i].data) {
            /* avoid the cost of new_packet + memcpy(->data) */
            memcpy(pkt, &nsv->ahead[i], sizeof(AVPacket));
            nsv->ahead[i].data = NULL; /* we ate that one */
            return pkt->size;
        }
    }

    /* this restaurant is not provisioned :^] */
    return -1;
}
