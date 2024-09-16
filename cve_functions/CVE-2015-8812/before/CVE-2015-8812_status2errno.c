static int status2errno(int status)
{
	switch (status) {
	case CPL_ERR_NONE:
		return 0;
	case CPL_ERR_CONN_RESET:
		return -ECONNRESET;
	case CPL_ERR_ARP_MISS:
		return -EHOSTUNREACH;
	case CPL_ERR_CONN_TIMEDOUT:
		return -ETIMEDOUT;
	case CPL_ERR_TCAM_FULL:
		return -ENOMEM;
	case CPL_ERR_CONN_EXIST:
		return -EADDRINUSE;
	default:
		return -EIO;
	}
}
