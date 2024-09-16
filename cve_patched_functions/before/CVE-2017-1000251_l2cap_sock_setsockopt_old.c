static int l2cap_sock_setsockopt_old(struct socket *sock, int optname, char __user *optval, int optlen)
{
	struct sock *sk = sock->sk;
	struct l2cap_options opts;
	int len, err = 0;
	u32 opt;

	BT_DBG("sk %p", sk);

	lock_sock(sk);

	switch (optname) {
	case L2CAP_OPTIONS:
		opts.imtu     = l2cap_pi(sk)->imtu;
		opts.omtu     = l2cap_pi(sk)->omtu;
		opts.flush_to = l2cap_pi(sk)->flush_to;
		opts.mode     = l2cap_pi(sk)->mode;

		len = min_t(unsigned int, sizeof(opts), optlen);
		if (copy_from_user((char *) &opts, optval, len)) {
			err = -EFAULT;
			break;
		}

		l2cap_pi(sk)->imtu = opts.imtu;
		l2cap_pi(sk)->omtu = opts.omtu;
		l2cap_pi(sk)->mode = opts.mode;
		break;

	case L2CAP_LM:
		if (get_user(opt, (u32 __user *) optval)) {
			err = -EFAULT;
			break;
		}

		if (opt & L2CAP_LM_AUTH)
			l2cap_pi(sk)->sec_level = BT_SECURITY_LOW;
		if (opt & L2CAP_LM_ENCRYPT)
			l2cap_pi(sk)->sec_level = BT_SECURITY_MEDIUM;
		if (opt & L2CAP_LM_SECURE)
			l2cap_pi(sk)->sec_level = BT_SECURITY_HIGH;

		l2cap_pi(sk)->role_switch    = (opt & L2CAP_LM_MASTER);
		l2cap_pi(sk)->force_reliable = (opt & L2CAP_LM_RELIABLE);
		break;

	default:
		err = -ENOPROTOOPT;
		break;
	}

	release_sock(sk);
	return err;
}
