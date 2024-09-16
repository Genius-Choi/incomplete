static int sctp_setsockopt_hmac_ident(struct sock *sk,
				      char __user *optval,
				      unsigned int optlen)
{
	struct sctp_endpoint *ep = sctp_sk(sk)->ep;
	struct sctp_hmacalgo *hmacs;
	u32 idents;
	int err;

	if (!ep->auth_enable)
		return -EACCES;

	if (optlen < sizeof(struct sctp_hmacalgo))
		return -EINVAL;

	hmacs = memdup_user(optval, optlen);
	if (IS_ERR(hmacs))
		return PTR_ERR(hmacs);

	idents = hmacs->shmac_num_idents;
	if (idents == 0 || idents > SCTP_AUTH_NUM_HMACS ||
	    (idents * sizeof(u16)) > (optlen - sizeof(struct sctp_hmacalgo))) {
		err = -EINVAL;
		goto out;
	}

	err = sctp_auth_ep_set_hmacs(ep, hmacs);
out:
	kfree(hmacs);
	return err;
}
