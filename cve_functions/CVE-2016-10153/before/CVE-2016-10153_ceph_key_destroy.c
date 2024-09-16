static void ceph_key_destroy(struct key *key)
{
	struct ceph_crypto_key *ckey = key->payload.data[0];

	ceph_crypto_key_destroy(ckey);
	kfree(ckey);
}
