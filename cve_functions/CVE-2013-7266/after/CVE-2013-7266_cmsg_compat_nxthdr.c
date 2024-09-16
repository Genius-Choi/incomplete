static inline struct compat_cmsghdr __user *cmsg_compat_nxthdr(struct msghdr *msg,
		struct compat_cmsghdr __user *cmsg, int cmsg_len)
{
	char __user *ptr = (char __user *)cmsg + CMSG_COMPAT_ALIGN(cmsg_len);
	if ((unsigned long)(ptr + 1 - (char __user *)msg->msg_control) >
			msg->msg_controllen)
		return NULL;
	return (struct compat_cmsghdr __user *)ptr;
}
