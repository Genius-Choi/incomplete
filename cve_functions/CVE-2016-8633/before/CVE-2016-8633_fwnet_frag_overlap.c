static bool fwnet_frag_overlap(struct fwnet_partial_datagram *pd,
			       unsigned offset, unsigned len)
{
	struct fwnet_fragment_info *fi;
	unsigned end = offset + len;

	list_for_each_entry(fi, &pd->fi_list, fi_link)
		if (offset < fi->offset + fi->len && end > fi->offset)
			return true;

	return false;
}
