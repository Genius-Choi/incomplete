static int ceph_x_create_authorizer(
	struct ceph_auth_client *ac, int peer_type,
	struct ceph_auth_handshake *auth)
{
	struct ceph_x_authorizer *au;
	struct ceph_x_ticket_handler *th;
	int ret;

	th = get_ticket_handler(ac, peer_type);
	if (IS_ERR(th))
		return PTR_ERR(th);

	au = kzalloc(sizeof(*au), GFP_NOFS);
	if (!au)
		return -ENOMEM;

	ret = ceph_x_build_authorizer(ac, th, au);
	if (ret) {
		kfree(au);
		return ret;
	}

	auth->authorizer = (struct ceph_authorizer *) au;
	auth->authorizer_buf = au->buf->vec.iov_base;
	auth->authorizer_buf_len = au->buf->vec.iov_len;
	auth->authorizer_reply_buf = au->reply_buf;
	auth->authorizer_reply_buf_len = sizeof (au->reply_buf);

	return 0;
}
