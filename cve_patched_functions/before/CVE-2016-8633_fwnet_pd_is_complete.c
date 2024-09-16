static bool fwnet_pd_is_complete(struct fwnet_partial_datagram *pd)
{
	struct fwnet_fragment_info *fi;

	fi = list_entry(pd->fi_list.next, struct fwnet_fragment_info, fi_link);

	return fi->len == pd->datagram_size;
}
