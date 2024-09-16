void pin_insert_group(struct fs_pin *pin, struct vfsmount *m, struct hlist_head *p)
{
	spin_lock(&pin_lock);
	if (p)
		hlist_add_head(&pin->s_list, p);
	hlist_add_head(&pin->m_list, &real_mount(m)->mnt_pins);
	spin_unlock(&pin_lock);
}
