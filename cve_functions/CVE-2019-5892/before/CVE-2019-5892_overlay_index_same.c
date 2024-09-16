static bool overlay_index_same(const struct attr *a1, const struct attr *a2)
{
	if (!a1 && a2)
		return false;
	if (!a2 && a1)
		return false;
	if (!a1 && !a2)
		return true;
	return !memcmp(&(a1->evpn_overlay), &(a2->evpn_overlay),
		       sizeof(struct overlay_index));
}
