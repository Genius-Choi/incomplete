void bitmap_writer_build_type_index(struct pack_idx_entry **index,
				    uint32_t index_nr)
{
	uint32_t i;

	writer.commits = ewah_new();
	writer.trees = ewah_new();
	writer.blobs = ewah_new();
	writer.tags = ewah_new();

	for (i = 0; i < index_nr; ++i) {
		struct object_entry *entry = (struct object_entry *)index[i];
		enum object_type real_type;

		entry->in_pack_pos = i;

		switch (entry->type) {
		case OBJ_COMMIT:
		case OBJ_TREE:
		case OBJ_BLOB:
		case OBJ_TAG:
			real_type = entry->type;
			break;

		default:
			real_type = sha1_object_info(entry->idx.sha1, NULL);
			break;
		}

		switch (real_type) {
		case OBJ_COMMIT:
			ewah_set(writer.commits, i);
			break;

		case OBJ_TREE:
			ewah_set(writer.trees, i);
			break;

		case OBJ_BLOB:
			ewah_set(writer.blobs, i);
			break;

		case OBJ_TAG:
			ewah_set(writer.tags, i);
			break;

		default:
			die("Missing type information for %s (%d/%d)",
			    sha1_to_hex(entry->idx.sha1), real_type, entry->type);
		}
	}
}
