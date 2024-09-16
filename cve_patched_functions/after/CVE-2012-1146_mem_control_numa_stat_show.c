static int mem_control_numa_stat_show(struct seq_file *m, void *arg)
{
	int nid;
	unsigned long total_nr, file_nr, anon_nr, unevictable_nr;
	unsigned long node_nr;
	struct cgroup *cont = m->private;
	struct mem_cgroup *mem_cont = mem_cgroup_from_cont(cont);

	total_nr = mem_cgroup_nr_lru_pages(mem_cont, LRU_ALL);
	seq_printf(m, "total=%lu", total_nr);
	for_each_node_state(nid, N_HIGH_MEMORY) {
		node_nr = mem_cgroup_node_nr_lru_pages(mem_cont, nid, LRU_ALL);
		seq_printf(m, " N%d=%lu", nid, node_nr);
	}
	seq_putc(m, '\n');

	file_nr = mem_cgroup_nr_lru_pages(mem_cont, LRU_ALL_FILE);
	seq_printf(m, "file=%lu", file_nr);
	for_each_node_state(nid, N_HIGH_MEMORY) {
		node_nr = mem_cgroup_node_nr_lru_pages(mem_cont, nid,
				LRU_ALL_FILE);
		seq_printf(m, " N%d=%lu", nid, node_nr);
	}
	seq_putc(m, '\n');

	anon_nr = mem_cgroup_nr_lru_pages(mem_cont, LRU_ALL_ANON);
	seq_printf(m, "anon=%lu", anon_nr);
	for_each_node_state(nid, N_HIGH_MEMORY) {
		node_nr = mem_cgroup_node_nr_lru_pages(mem_cont, nid,
				LRU_ALL_ANON);
		seq_printf(m, " N%d=%lu", nid, node_nr);
	}
	seq_putc(m, '\n');

	unevictable_nr = mem_cgroup_nr_lru_pages(mem_cont, BIT(LRU_UNEVICTABLE));
	seq_printf(m, "unevictable=%lu", unevictable_nr);
	for_each_node_state(nid, N_HIGH_MEMORY) {
		node_nr = mem_cgroup_node_nr_lru_pages(mem_cont, nid,
				BIT(LRU_UNEVICTABLE));
		seq_printf(m, " N%d=%lu", nid, node_nr);
	}
	seq_putc(m, '\n');
	return 0;
}
