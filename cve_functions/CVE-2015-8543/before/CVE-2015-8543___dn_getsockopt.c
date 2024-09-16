static int __dn_getsockopt(struct socket *sock, int level,int optname, char __user *optval,int __user *optlen, int flags)
{
	struct	sock *sk = sock->sk;
	struct dn_scp *scp = DN_SK(sk);
	struct linkinfo_dn link;
	unsigned int r_len;
	void *r_data = NULL;
	unsigned int val;

	if(get_user(r_len , optlen))
		return -EFAULT;

	switch (optname) {
	case DSO_CONDATA:
		if (r_len > sizeof(struct optdata_dn))
			r_len = sizeof(struct optdata_dn);
		r_data = &scp->conndata_in;
		break;

	case DSO_DISDATA:
		if (r_len > sizeof(struct optdata_dn))
			r_len = sizeof(struct optdata_dn);
		r_data = &scp->discdata_in;
		break;

	case DSO_CONACCESS:
		if (r_len > sizeof(struct accessdata_dn))
			r_len = sizeof(struct accessdata_dn);
		r_data = &scp->accessdata;
		break;

	case DSO_ACCEPTMODE:
		if (r_len > sizeof(unsigned char))
			r_len = sizeof(unsigned char);
		r_data = &scp->accept_mode;
		break;

	case DSO_LINKINFO:
		if (r_len > sizeof(struct linkinfo_dn))
			r_len = sizeof(struct linkinfo_dn);

		memset(&link, 0, sizeof(link));

		switch (sock->state) {
		case SS_CONNECTING:
			link.idn_linkstate = LL_CONNECTING;
			break;
		case SS_DISCONNECTING:
			link.idn_linkstate = LL_DISCONNECTING;
			break;
		case SS_CONNECTED:
			link.idn_linkstate = LL_RUNNING;
			break;
		default:
			link.idn_linkstate = LL_INACTIVE;
		}

		link.idn_segsize = scp->segsize_rem;
		r_data = &link;
		break;

	default:
#ifdef CONFIG_NETFILTER
	{
		int ret, len;

		if (get_user(len, optlen))
			return -EFAULT;

		ret = nf_getsockopt(sk, PF_DECnet, optname, optval, &len);
		if (ret >= 0)
			ret = put_user(len, optlen);
		return ret;
	}
#endif
	case DSO_STREAM:
	case DSO_SEQPACKET:
	case DSO_CONACCEPT:
	case DSO_CONREJECT:
		return -ENOPROTOOPT;

	case DSO_MAXWINDOW:
		if (r_len > sizeof(unsigned long))
			r_len = sizeof(unsigned long);
		r_data = &scp->max_window;
		break;

	case DSO_NODELAY:
		if (r_len > sizeof(int))
			r_len = sizeof(int);
		val = (scp->nonagle == 1);
		r_data = &val;
		break;

	case DSO_CORK:
		if (r_len > sizeof(int))
			r_len = sizeof(int);
		val = (scp->nonagle == 2);
		r_data = &val;
		break;

	case DSO_SERVICES:
		if (r_len > sizeof(unsigned char))
			r_len = sizeof(unsigned char);
		r_data = &scp->services_rem;
		break;

	case DSO_INFO:
		if (r_len > sizeof(unsigned char))
			r_len = sizeof(unsigned char);
		r_data = &scp->info_rem;
		break;
	}

	if (r_data) {
		if (copy_to_user(optval, r_data, r_len))
			return -EFAULT;
		if (put_user(r_len, optlen))
			return -EFAULT;
	}

	return 0;
}
