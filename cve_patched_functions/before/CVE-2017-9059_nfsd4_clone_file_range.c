__be32 nfsd4_clone_file_range(struct file *src, u64 src_pos, struct file *dst,
		u64 dst_pos, u64 count)
{
	return nfserrno(do_clone_file_range(src, src_pos, dst, dst_pos, count));
}
