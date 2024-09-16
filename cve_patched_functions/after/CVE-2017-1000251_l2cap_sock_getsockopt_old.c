static int l2cap_sock_getsockopt_old(struct socket *sock, int optname, char __user *optval, int __user *optlen)
{
	struct sock *sk = sock->sk;
	struct l2cap_options opts;
	struct l2cap_conninfo cinfo;
	int len, err = 0;
	u32 opt;

	BT_DBG("sk %p", sk);

	if (get_user(len, optlen))
		return -EFAULT;

	lock_sock(sk);

	switch (optname) {
	case L2CAP_OPTIONS:
		opts.imtu     = l2cap_pi(sk)->imtu;
		opts.omtu     = l2cap_pi(sk)->omtu;
		opts.flush_to = l2cap_pi(sk)->flush_to;
		opts.mode     = l2cap_pi(sk)->mode;

		len = min_t(unsigned int, len, sizeof(opts));
		if (copy_to_user(optval, (char *) &opts, len))
			err = -EFAULT;

		break;

	case L2CAP_LM:
		switch (l2cap_pi(sk)->sec_level) {
		case BT_SECURITY_LOW:
			opt = L2CAP_LM_AUTH;
			break;
		case BT_SECURITY_MEDIUM:
			opt = L2CAP_LM_AUTH | L2CAP_LM_ENCRYPT;
			break;
		case BT_SECURITY_HIGH:
			opt = L2CAP_LM_AUTH | L2CAP_LM_ENCRYPT |
							L2CAP_LM_SECURE;
			break;
		default:
			opt = 0;
			break;
		}

		if (l2cap_pi(sk)->role_switch)
			opt |= L2CAP_LM_MASTER;

		if (l2cap_pi(sk)->force_reliable)
			opt |= L2CAP_LM_RELIABLE;

		if (put_user(opt, (u32 __user *) optval))
			err = -EFAULT;
		break;

	case L2CAP_CONNINFO:
		if (sk->sk_state != BT_CONNECTED &&
					!(sk->sk_state == BT_CONNECT2 &&
						bt_sk(sk)->defer_setup)) {
			err = -ENOTCONN;
			break;
		}

		cinfo.hci_handle = l2cap_pi(sk)->conn->hcon->handle;
		memcpy(cinfo.dev_class, l2cap_pi(sk)->conn->hcon->dev_class, 3);

		len = min_t(unsigned int, len, sizeof(cinfo));
		if (copy_to_user(optval, (char *) &cinfo, len))
			err = -EFAULT;

		break;

	default:
		err = -ENOPROTOOPT;
		break;
	}

	release_sock(sk);
	return err;
}
