int ceph_x_init(struct ceph_auth_client *ac)
{
	struct ceph_x_info *xi;
	int ret;

	dout("ceph_x_init %p\n", ac);
	ret = -ENOMEM;
	xi = kzalloc(sizeof(*xi), GFP_NOFS);
	if (!xi)
		goto out;

	ret = -EINVAL;
	if (!ac->key) {
		pr_err("no secret set (for auth_x protocol)\n");
		goto out_nomem;
	}

	ret = ceph_crypto_key_clone(&xi->secret, ac->key);
	if (ret < 0) {
		pr_err("cannot clone key: %d\n", ret);
		goto out_nomem;
	}

	xi->starting = true;
	xi->ticket_handlers = RB_ROOT;

	ac->protocol = CEPH_AUTH_CEPHX;
	ac->private = xi;
	ac->ops = &ceph_x_ops;
	return 0;

out_nomem:
	kfree(xi);
out:
	return ret;
}
