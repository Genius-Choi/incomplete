static void ceph_x_reset(struct ceph_auth_client *ac)
{
	struct ceph_x_info *xi = ac->private;

	dout("reset\n");
	xi->starting = true;
	xi->server_challenge = 0;
}
