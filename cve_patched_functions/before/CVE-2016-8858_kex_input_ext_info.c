kex_input_ext_info(int type, u_int32_t seq, void *ctxt)
{
	struct ssh *ssh = ctxt;
	struct kex *kex = ssh->kex;
	u_int32_t i, ninfo;
	char *name, *val, *found;
	int r;

	debug("SSH2_MSG_EXT_INFO received");
	ssh_dispatch_set(ssh, SSH2_MSG_EXT_INFO, &kex_protocol_error);
	if ((r = sshpkt_get_u32(ssh, &ninfo)) != 0)
		return r;
	for (i = 0; i < ninfo; i++) {
		if ((r = sshpkt_get_cstring(ssh, &name, NULL)) != 0)
			return r;
		if ((r = sshpkt_get_cstring(ssh, &val, NULL)) != 0) {
			free(name);
			return r;
		}
		debug("%s: %s=<%s>", __func__, name, val);
		if (strcmp(name, "server-sig-algs") == 0) {
			found = match_list("rsa-sha2-256", val, NULL);
			if (found) {
				kex->rsa_sha2 = 256;
				free(found);
			}
			found = match_list("rsa-sha2-512", val, NULL);
			if (found) {
				kex->rsa_sha2 = 512;
				free(found);
			}
		}
		free(name);
		free(val);
	}
	return sshpkt_get_end(ssh);
}
