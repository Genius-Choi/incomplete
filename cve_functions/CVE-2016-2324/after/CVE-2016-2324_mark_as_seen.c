static inline void mark_as_seen(struct object *object)
{
	ALLOC_GROW(seen_objects, seen_objects_nr + 1, seen_objects_alloc);
	seen_objects[seen_objects_nr++] = object;
}
