static int dev_ifsioc(struct net *net, struct socket *sock,
			 unsigned int cmd, struct compat_ifreq __user *uifr32)
{
	struct ifreq __user *uifr;
	int err;

	uifr = compat_alloc_user_space(sizeof(*uifr));
	if (copy_in_user(uifr, uifr32, sizeof(*uifr32)))
		return -EFAULT;

	err = sock_do_ioctl(net, sock, cmd, (unsigned long)uifr);

	if (!err) {
		switch (cmd) {
		case SIOCGIFFLAGS:
		case SIOCGIFMETRIC:
		case SIOCGIFMTU:
		case SIOCGIFMEM:
		case SIOCGIFHWADDR:
		case SIOCGIFINDEX:
		case SIOCGIFADDR:
		case SIOCGIFBRDADDR:
		case SIOCGIFDSTADDR:
		case SIOCGIFNETMASK:
		case SIOCGIFPFLAGS:
		case SIOCGIFTXQLEN:
		case SIOCGMIIPHY:
		case SIOCGMIIREG:
			if (copy_in_user(uifr32, uifr, sizeof(*uifr32)))
				err = -EFAULT;
			break;
		}
	}
	return err;
}
