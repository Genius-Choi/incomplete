static int ceph_key_preparse(struct key_preparsed_payload *prep)
{
	struct ceph_crypto_key *ckey;
	size_t datalen = prep->datalen;
	int ret;
	void *p;

	ret = -EINVAL;
	if (datalen <= 0 || datalen > 32767 || !prep->data)
		goto err;

	ret = -ENOMEM;
	ckey = kmalloc(sizeof(*ckey), GFP_KERNEL);
	if (!ckey)
		goto err;

	/* TODO ceph_crypto_key_decode should really take const input */
	p = (void *)prep->data;
	ret = ceph_crypto_key_decode(ckey, &p, (char*)prep->data+datalen);
	if (ret < 0)
		goto err_ckey;

	prep->payload[0] = ckey;
	prep->quotalen = datalen;
	return 0;

err_ckey:
	kfree(ckey);
err:
	return ret;
}
