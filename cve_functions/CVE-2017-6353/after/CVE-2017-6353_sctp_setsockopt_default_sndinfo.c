static int sctp_setsockopt_default_sndinfo(struct sock *sk,
					   char __user *optval,
					   unsigned int optlen)
{
	struct sctp_sock *sp = sctp_sk(sk);
	struct sctp_association *asoc;
	struct sctp_sndinfo info;

	if (optlen != sizeof(info))
		return -EINVAL;
	if (copy_from_user(&info, optval, optlen))
		return -EFAULT;
	if (info.snd_flags &
	    ~(SCTP_UNORDERED | SCTP_ADDR_OVER |
	      SCTP_ABORT | SCTP_EOF))
		return -EINVAL;

	asoc = sctp_id2assoc(sk, info.snd_assoc_id);
	if (!asoc && info.snd_assoc_id && sctp_style(sk, UDP))
		return -EINVAL;
	if (asoc) {
		asoc->default_stream = info.snd_sid;
		asoc->default_flags = info.snd_flags;
		asoc->default_ppid = info.snd_ppid;
		asoc->default_context = info.snd_context;
	} else {
		sp->default_stream = info.snd_sid;
		sp->default_flags = info.snd_flags;
		sp->default_ppid = info.snd_ppid;
		sp->default_context = info.snd_context;
	}

	return 0;
}
