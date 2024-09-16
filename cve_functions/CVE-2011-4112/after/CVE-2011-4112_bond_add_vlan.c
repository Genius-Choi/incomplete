static int bond_add_vlan(struct bonding *bond, unsigned short vlan_id)
{
	struct vlan_entry *vlan;

	pr_debug("bond: %s, vlan id %d\n",
		 (bond ? bond->dev->name : "None"), vlan_id);

	vlan = kzalloc(sizeof(struct vlan_entry), GFP_KERNEL);
	if (!vlan)
		return -ENOMEM;

	INIT_LIST_HEAD(&vlan->vlan_list);
	vlan->vlan_id = vlan_id;

	write_lock_bh(&bond->lock);

	list_add_tail(&vlan->vlan_list, &bond->vlan_list);

	write_unlock_bh(&bond->lock);

	pr_debug("added VLAN ID %d on bond %s\n", vlan_id, bond->dev->name);

	return 0;
}
