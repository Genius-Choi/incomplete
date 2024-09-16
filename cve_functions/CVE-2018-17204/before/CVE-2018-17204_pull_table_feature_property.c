pull_table_feature_property(struct ofpbuf *msg, struct ofpbuf *payload,
                            uint64_t *typep)
{
    enum ofperr error;

    error = ofpprop_pull(msg, payload, typep);
    if (payload && !error) {
        ofpbuf_pull(payload, (char *)payload->msg - (char *)payload->header);
    }
    return error;
}
