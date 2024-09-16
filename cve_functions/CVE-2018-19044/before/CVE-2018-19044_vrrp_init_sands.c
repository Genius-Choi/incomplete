vrrp_init_sands(list l)
{
	vrrp_t *vrrp;
	element e;

	LIST_FOREACH(l, vrrp, e) {
		vrrp->sands.tv_sec = TIMER_DISABLED;
		rb_insert_sort_cached(&vrrp->sockets->rb_sands, vrrp, rb_sands, vrrp_timer_cmp);
		vrrp_init_instance_sands(vrrp);
		vrrp->reload_master = false;
	}
}
