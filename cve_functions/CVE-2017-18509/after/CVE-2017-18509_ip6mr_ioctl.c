int ip6mr_ioctl(struct sock *sk, int cmd, void __user *arg)
{
	struct sioc_sg_req6 sr;
	struct sioc_mif_req6 vr;
	struct mif_device *vif;
	struct mfc6_cache *c;
	struct net *net = sock_net(sk);
	struct mr6_table *mrt;

	mrt = ip6mr_get_table(net, raw6_sk(sk)->ip6mr_table ? : RT6_TABLE_DFLT);
	if (!mrt)
		return -ENOENT;

	switch (cmd) {
	case SIOCGETMIFCNT_IN6:
		if (copy_from_user(&vr, arg, sizeof(vr)))
			return -EFAULT;
		if (vr.mifi >= mrt->maxvif)
			return -EINVAL;
		read_lock(&mrt_lock);
		vif = &mrt->vif6_table[vr.mifi];
		if (MIF_EXISTS(mrt, vr.mifi)) {
			vr.icount = vif->pkt_in;
			vr.ocount = vif->pkt_out;
			vr.ibytes = vif->bytes_in;
			vr.obytes = vif->bytes_out;
			read_unlock(&mrt_lock);

			if (copy_to_user(arg, &vr, sizeof(vr)))
				return -EFAULT;
			return 0;
		}
		read_unlock(&mrt_lock);
		return -EADDRNOTAVAIL;
	case SIOCGETSGCNT_IN6:
		if (copy_from_user(&sr, arg, sizeof(sr)))
			return -EFAULT;

		read_lock(&mrt_lock);
		c = ip6mr_cache_find(mrt, &sr.src.sin6_addr, &sr.grp.sin6_addr);
		if (c) {
			sr.pktcnt = c->mfc_un.res.pkt;
			sr.bytecnt = c->mfc_un.res.bytes;
			sr.wrong_if = c->mfc_un.res.wrong_if;
			read_unlock(&mrt_lock);

			if (copy_to_user(arg, &sr, sizeof(sr)))
				return -EFAULT;
			return 0;
		}
		read_unlock(&mrt_lock);
		return -EADDRNOTAVAIL;
	default:
		return -ENOIOCTLCMD;
	}
}
