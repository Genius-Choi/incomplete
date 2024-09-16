static void attr_show_all_iterator(struct hash_backet *backet, struct vty *vty)
{
	struct attr *attr = backet->data;

	vty_out(vty, "attr[%ld] nexthop %s\n", attr->refcnt,
		inet_ntoa(attr->nexthop));
	vty_out(vty, "\tflags: %" PRIu64 " med: %u local_pref: %u origin: %u weight: %u label: %u\n",
		attr->flag, attr->med, attr->local_pref, attr->origin,
		attr->weight, attr->label);
}
