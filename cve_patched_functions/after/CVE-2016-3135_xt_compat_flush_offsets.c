void xt_compat_flush_offsets(u_int8_t af)
{
	if (xt[af].compat_tab) {
		vfree(xt[af].compat_tab);
		xt[af].compat_tab = NULL;
		xt[af].number = 0;
		xt[af].cur = 0;
	}
}
