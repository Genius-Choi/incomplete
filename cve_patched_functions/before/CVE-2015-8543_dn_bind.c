static int dn_bind(struct socket *sock, struct sockaddr *uaddr, int addr_len)
{
	struct sock *sk = sock->sk;
	struct dn_scp *scp = DN_SK(sk);
	struct sockaddr_dn *saddr = (struct sockaddr_dn *)uaddr;
	struct net_device *dev, *ldev;
	int rv;

	if (addr_len != sizeof(struct sockaddr_dn))
		return -EINVAL;

	if (saddr->sdn_family != AF_DECnet)
		return -EINVAL;

	if (le16_to_cpu(saddr->sdn_nodeaddrl) && (le16_to_cpu(saddr->sdn_nodeaddrl) != 2))
		return -EINVAL;

	if (le16_to_cpu(saddr->sdn_objnamel) > DN_MAXOBJL)
		return -EINVAL;

	if (saddr->sdn_flags & ~SDF_WILD)
		return -EINVAL;

	if (!capable(CAP_NET_BIND_SERVICE) && (saddr->sdn_objnum ||
	    (saddr->sdn_flags & SDF_WILD)))
		return -EACCES;

	if (!(saddr->sdn_flags & SDF_WILD)) {
		if (le16_to_cpu(saddr->sdn_nodeaddrl)) {
			rcu_read_lock();
			ldev = NULL;
			for_each_netdev_rcu(&init_net, dev) {
				if (!dev->dn_ptr)
					continue;
				if (dn_dev_islocal(dev, dn_saddr2dn(saddr))) {
					ldev = dev;
					break;
				}
			}
			rcu_read_unlock();
			if (ldev == NULL)
				return -EADDRNOTAVAIL;
		}
	}

	rv = -EINVAL;
	lock_sock(sk);
	if (sock_flag(sk, SOCK_ZAPPED)) {
		memcpy(&scp->addr, saddr, addr_len);
		sock_reset_flag(sk, SOCK_ZAPPED);

		rv = dn_hash_sock(sk);
		if (rv)
			sock_set_flag(sk, SOCK_ZAPPED);
	}
	release_sock(sk);

	return rv;
}
