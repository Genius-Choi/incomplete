static void inetdev_changename(struct net_device *dev, struct in_device *in_dev)
{
	struct in_ifaddr *ifa;
	int named = 0;

	for (ifa = in_dev->ifa_list; ifa; ifa = ifa->ifa_next) {
		char old[IFNAMSIZ], *dot;

		memcpy(old, ifa->ifa_label, IFNAMSIZ);
		memcpy(ifa->ifa_label, dev->name, IFNAMSIZ);
		if (named++ == 0)
			goto skip;
		dot = strchr(old, ':');
		if (!dot) {
			sprintf(old, ":%d", named);
			dot = old;
		}
		if (strlen(dot) + strlen(dev->name) < IFNAMSIZ)
			strcat(ifa->ifa_label, dot);
		else
			strcpy(ifa->ifa_label + (IFNAMSIZ - strlen(dot) - 1), dot);
skip:
		rtmsg_ifa(RTM_NEWADDR, ifa, NULL, 0);
	}
}
