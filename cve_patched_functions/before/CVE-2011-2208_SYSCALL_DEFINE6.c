SYSCALL_DEFINE6(osf_mmap, unsigned long, addr, unsigned long, len,
		unsigned long, prot, unsigned long, flags, unsigned long, fd,
		unsigned long, off)
{
	unsigned long ret = -EINVAL;

#if 0
	if (flags & (_MAP_HASSEMAPHORE | _MAP_INHERIT | _MAP_UNALIGNED))
		printk("%s: unimplemented OSF mmap flags %04lx\n", 
			current->comm, flags);
#endif
	if ((off + PAGE_ALIGN(len)) < off)
		goto out;
	if (off & ~PAGE_MASK)
		goto out;
	ret = sys_mmap_pgoff(addr, len, prot, flags, fd, off >> PAGE_SHIFT);
 out:
	return ret;
}
