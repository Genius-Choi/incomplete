static int m_show(struct seq_file *m, void *v)
{
	struct proc_mounts *p = m->private;
	struct mount *r = list_entry(v, struct mount, mnt_list);
	return p->show(m, &r->mnt);
}
