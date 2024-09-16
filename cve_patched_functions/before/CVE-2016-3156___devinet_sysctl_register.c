static int __devinet_sysctl_register(struct net *net, char *dev_name,
					struct ipv4_devconf *p)
{
	int i;
	struct devinet_sysctl_table *t;
	char path[sizeof("net/ipv4/conf/") + IFNAMSIZ];

	t = kmemdup(&devinet_sysctl, sizeof(*t), GFP_KERNEL);
	if (!t)
		goto out;

	for (i = 0; i < ARRAY_SIZE(t->devinet_vars) - 1; i++) {
		t->devinet_vars[i].data += (char *)p - (char *)&ipv4_devconf;
		t->devinet_vars[i].extra1 = p;
		t->devinet_vars[i].extra2 = net;
	}

	snprintf(path, sizeof(path), "net/ipv4/conf/%s", dev_name);

	t->sysctl_header = register_net_sysctl(net, path, t->devinet_vars);
	if (!t->sysctl_header)
		goto free;

	p->sysctl = t;
	return 0;

free:
	kfree(t);
out:
	return -ENOBUFS;
}
