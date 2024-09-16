static void write_selected_commits_v1(struct sha1file *f,
				      struct pack_idx_entry **index,
				      uint32_t index_nr)
{
	int i;

	for (i = 0; i < writer.selected_nr; ++i) {
		struct bitmapped_commit *stored = &writer.selected[i];

		int commit_pos =
			sha1_pos(stored->commit->object.oid.hash, index, index_nr, sha1_access);

		if (commit_pos < 0)
			die("BUG: trying to write commit not in index");

		sha1write_be32(f, commit_pos);
		sha1write_u8(f, stored->xor_offset);
		sha1write_u8(f, stored->flags);

		dump_bitmap(f, stored->write_as);
	}
}
