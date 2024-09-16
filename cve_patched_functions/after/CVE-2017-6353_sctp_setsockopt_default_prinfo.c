static int sctp_setsockopt_default_prinfo(struct sock *sk,
					  char __user *optval,
					  unsigned int optlen)
{
	struct sctp_default_prinfo info;
	struct sctp_association *asoc;
	int retval = -EINVAL;

	if (optlen != sizeof(info))
		goto out;

	if (copy_from_user(&info, optval, sizeof(info))) {
		retval = -EFAULT;
		goto out;
	}

	if (info.pr_policy & ~SCTP_PR_SCTP_MASK)
		goto out;

	if (info.pr_policy == SCTP_PR_SCTP_NONE)
		info.pr_value = 0;

	asoc = sctp_id2assoc(sk, info.pr_assoc_id);
	if (asoc) {
		SCTP_PR_SET_POLICY(asoc->default_flags, info.pr_policy);
		asoc->default_timetolive = info.pr_value;
	} else if (!info.pr_assoc_id) {
		struct sctp_sock *sp = sctp_sk(sk);

		SCTP_PR_SET_POLICY(sp->default_flags, info.pr_policy);
		sp->default_timetolive = info.pr_value;
	} else {
		goto out;
	}

	retval = 0;

out:
	return retval;
}
