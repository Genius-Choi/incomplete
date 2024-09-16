static void ceph_x_destroy(struct ceph_auth_client *ac)
{
	struct ceph_x_info *xi = ac->private;
	struct rb_node *p;

	dout("ceph_x_destroy %p\n", ac);
	ceph_crypto_key_destroy(&xi->secret);

	while ((p = rb_first(&xi->ticket_handlers)) != NULL) {
		struct ceph_x_ticket_handler *th =
			rb_entry(p, struct ceph_x_ticket_handler, node);
		remove_ticket_handler(ac, th);
	}

	if (xi->auth_authorizer.buf)
		ceph_buffer_put(xi->auth_authorizer.buf);

	kfree(ac->private);
	ac->private = NULL;
}
