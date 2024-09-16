parse_ENQUEUE(char *arg, struct ofpbuf *ofpacts,
              enum ofputil_protocol *usable_protocols OVS_UNUSED)
{
    char *sp = NULL;
    char *port = strtok_r(arg, ":q,", &sp);
    char *queue = strtok_r(NULL, "", &sp);
    struct ofpact_enqueue *enqueue;

    if (port == NULL || queue == NULL) {
        return xstrdup("\"enqueue\" syntax is \"enqueue:PORT:QUEUE\" or "
                       "\"enqueue(PORT,QUEUE)\"");
    }

    enqueue = ofpact_put_ENQUEUE(ofpacts);
    if (!ofputil_port_from_string(port, &enqueue->port)) {
        return xasprintf("%s: enqueue to unknown port", port);
    }
    return str_to_u32(queue, &enqueue->queue);
}
