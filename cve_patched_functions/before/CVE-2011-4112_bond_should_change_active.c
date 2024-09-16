static bool bond_should_change_active(struct bonding *bond)
{
	struct slave *prim = bond->primary_slave;
	struct slave *curr = bond->curr_active_slave;

	if (!prim || !curr || curr->link != BOND_LINK_UP)
		return true;
	if (bond->force_primary) {
		bond->force_primary = false;
		return true;
	}
	if (bond->params.primary_reselect == BOND_PRI_RESELECT_BETTER &&
	    (prim->speed < curr->speed ||
	     (prim->speed == curr->speed && prim->duplex <= curr->duplex)))
		return false;
	if (bond->params.primary_reselect == BOND_PRI_RESELECT_FAILURE)
		return false;
	return true;
}
