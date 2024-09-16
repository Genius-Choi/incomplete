static void sysctl_set_parent(struct ctl_table *parent, struct ctl_table *table)
{
	for (; table->procname; table++) {
		table->parent = parent;
		if (table->child)
			sysctl_set_parent(table, table->child);
	}
}
