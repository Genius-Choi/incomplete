static int smaps_pte_hole(unsigned long addr, unsigned long end,
		struct mm_walk *walk)
{
	struct mem_size_stats *mss = walk->private;

	mss->swap += shmem_partial_swap_usage(
			walk->vma->vm_file->f_mapping, addr, end);

	return 0;
}
