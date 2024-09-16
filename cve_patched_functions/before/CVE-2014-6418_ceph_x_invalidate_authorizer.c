static void ceph_x_invalidate_authorizer(struct ceph_auth_client *ac,
				   int peer_type)
{
	struct ceph_x_ticket_handler *th;

	th = get_ticket_handler(ac, peer_type);
	if (!IS_ERR(th))
		memset(&th->validity, 0, sizeof(th->validity));
}
