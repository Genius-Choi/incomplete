static int macvtap_set_queue(struct net_device *dev, struct file *file,
				struct macvtap_queue *q)
{
	struct macvlan_dev *vlan = netdev_priv(dev);
	int index;
	int err = -EBUSY;

	spin_lock(&macvtap_lock);
	if (vlan->numvtaps == MAX_MACVTAP_QUEUES)
		goto out;

	err = 0;
	index = get_slot(vlan, NULL);
	rcu_assign_pointer(q->vlan, vlan);
	rcu_assign_pointer(vlan->taps[index], q);
	sock_hold(&q->sk);

	q->file = file;
	file->private_data = q;

	vlan->numvtaps++;

out:
	spin_unlock(&macvtap_lock);
	return err;
}
