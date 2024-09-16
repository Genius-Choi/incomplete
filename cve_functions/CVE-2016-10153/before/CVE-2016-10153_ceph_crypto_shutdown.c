void ceph_crypto_shutdown(void) {
	unregister_key_type(&key_type_ceph);
}
