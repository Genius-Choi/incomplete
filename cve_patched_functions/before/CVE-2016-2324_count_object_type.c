static uint32_t count_object_type(struct bitmap *objects,
				  enum object_type type)
{
	struct eindex *eindex = &bitmap_git.ext_index;

	uint32_t i = 0, count = 0;
	struct ewah_iterator it;
	eword_t filter;

	switch (type) {
	case OBJ_COMMIT:
		ewah_iterator_init(&it, bitmap_git.commits);
		break;

	case OBJ_TREE:
		ewah_iterator_init(&it, bitmap_git.trees);
		break;

	case OBJ_BLOB:
		ewah_iterator_init(&it, bitmap_git.blobs);
		break;

	case OBJ_TAG:
		ewah_iterator_init(&it, bitmap_git.tags);
		break;

	default:
		return 0;
	}

	while (i < objects->word_alloc && ewah_iterator_next(&filter, &it)) {
		eword_t word = objects->words[i++] & filter;
		count += ewah_bit_popcount64(word);
	}

	for (i = 0; i < eindex->count; ++i) {
		if (eindex->objects[i]->type == type &&
			bitmap_get(objects, bitmap_git.pack->num_objects + i))
			count++;
	}

	return count;
}
