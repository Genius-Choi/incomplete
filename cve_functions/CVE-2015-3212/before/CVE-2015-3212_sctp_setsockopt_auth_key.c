static int sctp_setsockopt_auth_key(struct sock *sk,
				    char __user *optval,
				    unsigned int optlen)
{
	struct sctp_endpoint *ep = sctp_sk(sk)->ep;
	struct sctp_authkey *authkey;
	struct sctp_association *asoc;
	int ret;

	if (!ep->auth_enable)
		return -EACCES;

	if (optlen <= sizeof(struct sctp_authkey))
		return -EINVAL;

	authkey = memdup_user(optval, optlen);
	if (IS_ERR(authkey))
		return PTR_ERR(authkey);

	if (authkey->sca_keylength > optlen - sizeof(struct sctp_authkey)) {
		ret = -EINVAL;
		goto out;
	}

	asoc = sctp_id2assoc(sk, authkey->sca_assoc_id);
	if (!asoc && authkey->sca_assoc_id && sctp_style(sk, UDP)) {
		ret = -EINVAL;
		goto out;
	}

	ret = sctp_auth_set_key(ep, asoc, authkey);
out:
	kzfree(authkey);
	return ret;
}
