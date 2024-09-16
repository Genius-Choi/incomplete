static int bond_has_this_ip(struct bonding *bond, __be32 ip)
{
	struct vlan_entry *vlan;

	if (ip == bond->master_ip)
		return 1;

	list_for_each_entry(vlan, &bond->vlan_list, vlan_list) {
		if (ip == vlan->vlan_ip)
			return 1;
	}

	return 0;
}
