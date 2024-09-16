static void try_attach(struct ctl_table_header *p, struct ctl_table_header *q)
{
	struct ctl_table *to = p->ctl_table, *by = q->ctl_table;
	struct ctl_table *next;
	int is_better = 0;
	int not_in_parent = !p->attached_by;

	while ((next = is_branch_in(by, to)) != NULL) {
		if (by == q->attached_by)
			is_better = 1;
		if (to == p->attached_by)
			not_in_parent = 1;
		by = by->child;
		to = next->child;
	}

	if (is_better && not_in_parent) {
		q->attached_by = by;
		q->attached_to = to;
		q->parent = p;
	}
}
