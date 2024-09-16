static void bond_validate_arp(struct bonding *bond, struct slave *slave, __be32 sip, __be32 tip)
{
	int i;
	__be32 *targets = bond->params.arp_targets;

	for (i = 0; (i < BOND_MAX_ARP_TARGETS) && targets[i]; i++) {
		pr_debug("bva: sip %pI4 tip %pI4 t[%d] %pI4 bhti(tip) %d\n",
			 &sip, &tip, i, &targets[i],
			 bond_has_this_ip(bond, tip));
		if (sip == targets[i]) {
			if (bond_has_this_ip(bond, tip))
				slave->last_arp_rx = jiffies;
			return;
		}
	}
}
