server_headers(struct client *clt, void *descp,
    int (*hdr_cb)(struct client *, struct kv *, void *), void *arg)
{
	struct kv		*hdr, *kv;
	struct http_descriptor	*desc = descp;

	RB_FOREACH(hdr, kvtree, &desc->http_headers) {
		if ((hdr_cb)(clt, hdr, arg) == -1)
			return (-1);
		TAILQ_FOREACH(kv, &hdr->kv_children, kv_entry) {
			if ((hdr_cb)(clt, kv, arg) == -1)
				return (-1);
		}
	}

	return (0);
}
