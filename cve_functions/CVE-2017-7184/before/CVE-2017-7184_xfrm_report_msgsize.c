static inline size_t xfrm_report_msgsize(void)
{
	return NLMSG_ALIGN(sizeof(struct xfrm_user_report));
}
