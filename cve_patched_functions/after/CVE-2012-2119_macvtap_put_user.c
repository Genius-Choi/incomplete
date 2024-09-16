static ssize_t macvtap_put_user(struct macvtap_queue *q,
				const struct sk_buff *skb,
				const struct iovec *iv, int len)
{
	struct macvlan_dev *vlan;
	int ret;
	int vnet_hdr_len = 0;

	if (q->flags & IFF_VNET_HDR) {
		struct virtio_net_hdr vnet_hdr;
		vnet_hdr_len = q->vnet_hdr_sz;
		if ((len -= vnet_hdr_len) < 0)
			return -EINVAL;

		ret = macvtap_skb_to_vnet_hdr(skb, &vnet_hdr);
		if (ret)
			return ret;

		if (memcpy_toiovecend(iv, (void *)&vnet_hdr, 0, sizeof(vnet_hdr)))
			return -EFAULT;
	}

	len = min_t(int, skb->len, len);

	ret = skb_copy_datagram_const_iovec(skb, 0, iv, vnet_hdr_len, len);

	rcu_read_lock_bh();
	vlan = rcu_dereference_bh(q->vlan);
	if (vlan)
		macvlan_count_rx(vlan, len, ret == 0, 0);
	rcu_read_unlock_bh();

	return ret ? ret : (len + vnet_hdr_len);
}
