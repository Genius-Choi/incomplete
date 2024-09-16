static void _out_packet_queue(s2s_t s2s, pkt_t pkt) {
    char *rkey = s2s_route_key(NULL, pkt->from->domain, pkt->to->domain);
    jqueue_t q = (jqueue_t) xhash_get(s2s->outq, rkey);

    if(q == NULL) {
        log_debug(ZONE, "creating new out packet queue for '%s'", rkey);
        q = jqueue_new();
        q->key = rkey;
        xhash_put(s2s->outq, q->key, (void *) q);
    } else {
        free(rkey);
    }

    log_debug(ZONE, "queueing packet for '%s'", q->key);

    jqueue_push(q, (void *) pkt, 0);
}
