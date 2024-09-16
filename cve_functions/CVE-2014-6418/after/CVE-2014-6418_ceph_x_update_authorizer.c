static int ceph_x_update_authorizer(
	struct ceph_auth_client *ac, int peer_type,
	struct ceph_auth_handshake *auth)
{
	struct ceph_x_authorizer *au;
	struct ceph_x_ticket_handler *th;

	th = get_ticket_handler(ac, peer_type);
	if (IS_ERR(th))
		return PTR_ERR(th);

	au = (struct ceph_x_authorizer *)auth->authorizer;
	if (au->secret_id < th->secret_id) {
		dout("ceph_x_update_authorizer service %u secret %llu < %llu\n",
		     au->service, au->secret_id, th->secret_id);
		return ceph_x_build_authorizer(ac, th, au);
	}
	return 0;
}
