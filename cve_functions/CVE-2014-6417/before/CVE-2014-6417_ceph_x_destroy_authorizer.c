static void ceph_x_destroy_authorizer(struct ceph_auth_client *ac,
				      struct ceph_authorizer *a)
{
	struct ceph_x_authorizer *au = (void *)a;

	ceph_buffer_put(au->buf);
	kfree(au);
}
