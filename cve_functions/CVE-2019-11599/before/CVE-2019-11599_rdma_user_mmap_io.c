int rdma_user_mmap_io(struct ib_ucontext *ucontext, struct vm_area_struct *vma,
		      unsigned long pfn, unsigned long size, pgprot_t prot)
{
	struct rdma_umap_priv *priv = rdma_user_mmap_pre(ucontext, vma, size);

	if (IS_ERR(priv))
		return PTR_ERR(priv);

	vma->vm_page_prot = prot;
	if (io_remap_pfn_range(vma, vma->vm_start, pfn, size, prot)) {
		kfree(priv);
		return -EAGAIN;
	}

	rdma_umap_priv_init(priv, vma);
	return 0;
}
