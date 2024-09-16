static int pppol2tp_tunnel_getsockopt(struct sock *sk,
				      struct l2tp_tunnel *tunnel,
				      int optname, int *val)
{
	int err = 0;

	switch (optname) {
	case PPPOL2TP_SO_DEBUG:
		*val = tunnel->debug;
		l2tp_info(tunnel, PPPOL2TP_MSG_CONTROL, "%s: get debug=%x\n",
			  tunnel->name, tunnel->debug);
		break;

	default:
		err = -ENOPROTOOPT;
		break;
	}

	return err;
}
