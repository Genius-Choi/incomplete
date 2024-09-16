static int verify_newpolicy_info(struct xfrm_userpolicy_info *p)
{
	int ret;

	switch (p->share) {
	case XFRM_SHARE_ANY:
	case XFRM_SHARE_SESSION:
	case XFRM_SHARE_USER:
	case XFRM_SHARE_UNIQUE:
		break;

	default:
		return -EINVAL;
	}

	switch (p->action) {
	case XFRM_POLICY_ALLOW:
	case XFRM_POLICY_BLOCK:
		break;

	default:
		return -EINVAL;
	}

	switch (p->sel.family) {
	case AF_INET:
		break;

	case AF_INET6:
#if IS_ENABLED(CONFIG_IPV6)
		break;
#else
		return  -EAFNOSUPPORT;
#endif

	default:
		return -EINVAL;
	}

	ret = verify_policy_dir(p->dir);
	if (ret)
		return ret;
	if (p->index && ((p->index & XFRM_POLICY_MAX) != p->dir))
		return -EINVAL;

	return 0;
}
