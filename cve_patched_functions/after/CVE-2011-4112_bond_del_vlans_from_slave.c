static void bond_del_vlans_from_slave(struct bonding *bond,
				      struct net_device *slave_dev)
{
	const struct net_device_ops *slave_ops = slave_dev->netdev_ops;
	struct vlan_entry *vlan;

	if (!(slave_dev->features & NETIF_F_HW_VLAN_FILTER) ||
	    !(slave_ops->ndo_vlan_rx_kill_vid))
		return;

	list_for_each_entry(vlan, &bond->vlan_list, vlan_list) {
		if (!vlan->vlan_id)
			continue;
		slave_ops->ndo_vlan_rx_kill_vid(slave_dev, vlan->vlan_id);
	}
}
