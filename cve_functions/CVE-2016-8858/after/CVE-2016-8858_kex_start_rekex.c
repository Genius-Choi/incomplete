kex_start_rekex(struct ssh *ssh)
{
	if (ssh->kex == NULL) {
		error("%s: no kex", __func__);
		return SSH_ERR_INTERNAL_ERROR;
	}
	if (ssh->kex->done == 0) {
		error("%s: requested twice", __func__);
		return SSH_ERR_INTERNAL_ERROR;
	}
	ssh->kex->done = 0;
	return kex_send_kexinit(ssh);
}
