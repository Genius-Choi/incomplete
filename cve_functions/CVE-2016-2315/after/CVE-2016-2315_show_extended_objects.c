static void show_extended_objects(struct bitmap *objects,
				  show_reachable_fn show_reach)
{
	struct eindex *eindex = &bitmap_git.ext_index;
	uint32_t i;

	for (i = 0; i < eindex->count; ++i) {
		struct object *obj;

		if (!bitmap_get(objects, bitmap_git.pack->num_objects + i))
			continue;

		obj = eindex->objects[i];
		show_reach(obj->oid.hash, obj->type, 0, eindex->hashes[i], NULL, 0);
	}
}
