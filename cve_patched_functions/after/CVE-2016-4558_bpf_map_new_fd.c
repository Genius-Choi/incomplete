int bpf_map_new_fd(struct bpf_map *map)
{
	return anon_inode_getfd("bpf-map", &bpf_map_fops, map,
				O_RDWR | O_CLOEXEC);
}
