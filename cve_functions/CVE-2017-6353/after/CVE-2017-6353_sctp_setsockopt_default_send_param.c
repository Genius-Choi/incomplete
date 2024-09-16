static int sctp_setsockopt_default_send_param(struct sock *sk,
					      char __user *optval,
					      unsigned int optlen)
{
	struct sctp_sock *sp = sctp_sk(sk);
	struct sctp_association *asoc;
	struct sctp_sndrcvinfo info;

	if (optlen != sizeof(info))
		return -EINVAL;
	if (copy_from_user(&info, optval, optlen))
		return -EFAULT;
	if (info.sinfo_flags &
	    ~(SCTP_UNORDERED | SCTP_ADDR_OVER |
	      SCTP_ABORT | SCTP_EOF))
		return -EINVAL;

	asoc = sctp_id2assoc(sk, info.sinfo_assoc_id);
	if (!asoc && info.sinfo_assoc_id && sctp_style(sk, UDP))
		return -EINVAL;
	if (asoc) {
		asoc->default_stream = info.sinfo_stream;
		asoc->default_flags = info.sinfo_flags;
		asoc->default_ppid = info.sinfo_ppid;
		asoc->default_context = info.sinfo_context;
		asoc->default_timetolive = info.sinfo_timetolive;
	} else {
		sp->default_stream = info.sinfo_stream;
		sp->default_flags = info.sinfo_flags;
		sp->default_ppid = info.sinfo_ppid;
		sp->default_context = info.sinfo_context;
		sp->default_timetolive = info.sinfo_timetolive;
	}

	return 0;
}
