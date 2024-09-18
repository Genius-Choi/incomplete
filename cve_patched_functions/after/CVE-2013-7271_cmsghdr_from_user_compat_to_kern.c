int cmsghdr_from_user_compat_to_kern(struct msghdr *kmsg, struct sock *sk,
			       unsigned char *stackbuf, int stackbuf_size)
{
	struct compat_cmsghdr __user *ucmsg;
	struct cmsghdr *kcmsg, *kcmsg_base;
	compat_size_t ucmlen;
	__kernel_size_t kcmlen, tmp;
	int err = -EFAULT;

	kcmlen = 0;
	kcmsg_base = kcmsg = (struct cmsghdr *)stackbuf;
	ucmsg = CMSG_COMPAT_FIRSTHDR(kmsg);
	while (ucmsg != NULL) {
		if (get_user(ucmlen, &ucmsg->cmsg_len))
			return -EFAULT;

		/* Catch bogons. */
		if (!CMSG_COMPAT_OK(ucmlen, ucmsg, kmsg))
			return -EINVAL;

		tmp = ((ucmlen - CMSG_COMPAT_ALIGN(sizeof(*ucmsg))) +
		       CMSG_ALIGN(sizeof(struct cmsghdr)));
		tmp = CMSG_ALIGN(tmp);
		kcmlen += tmp;
		ucmsg = cmsg_compat_nxthdr(kmsg, ucmsg, ucmlen);
	}
	if (kcmlen == 0)
		return -EINVAL;

	/* The kcmlen holds the 64-bit version of the control length.
	 * It may not be modified as we do not stick it into the kmsg
	 * until we have successfully copied over all of the data
	 * from the user.
	 */
	if (kcmlen > stackbuf_size)
		kcmsg_base = kcmsg = sock_kmalloc(sk, kcmlen, GFP_KERNEL);
	if (kcmsg == NULL)
		return -ENOBUFS;

	/* Now copy them over neatly. */
	memset(kcmsg, 0, kcmlen);
	ucmsg = CMSG_COMPAT_FIRSTHDR(kmsg);
	while (ucmsg != NULL) {
		if (__get_user(ucmlen, &ucmsg->cmsg_len))
			goto Efault;
		if (!CMSG_COMPAT_OK(ucmlen, ucmsg, kmsg))
			goto Einval;
		tmp = ((ucmlen - CMSG_COMPAT_ALIGN(sizeof(*ucmsg))) +
		       CMSG_ALIGN(sizeof(struct cmsghdr)));
		if ((char *)kcmsg_base + kcmlen - (char *)kcmsg < CMSG_ALIGN(tmp))
			goto Einval;
		kcmsg->cmsg_len = tmp;
		tmp = CMSG_ALIGN(tmp);
		if (__get_user(kcmsg->cmsg_level, &ucmsg->cmsg_level) ||
		    __get_user(kcmsg->cmsg_type, &ucmsg->cmsg_type) ||
		    copy_from_user(CMSG_DATA(kcmsg),
				   CMSG_COMPAT_DATA(ucmsg),
				   (ucmlen - CMSG_COMPAT_ALIGN(sizeof(*ucmsg)))))
			goto Efault;

		/* Advance. */
		kcmsg = (struct cmsghdr *)((char *)kcmsg + tmp);
		ucmsg = cmsg_compat_nxthdr(kmsg, ucmsg, ucmlen);
	}

	/* Ok, looks like we made it.  Hook it up and return success. */
	kmsg->msg_control = kcmsg_base;
	kmsg->msg_controllen = kcmlen;
	return 0;

Einval:
	err = -EINVAL;
Efault:
	if (kcmsg_base != (struct cmsghdr *)stackbuf)
		sock_kfree_s(sk, kcmsg_base, kcmlen);
	return err;
}
