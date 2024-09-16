static inline void reset_all_seen(void)
{
	unsigned int i;
	for (i = 0; i < seen_objects_nr; ++i) {
		seen_objects[i]->flags &= ~(SEEN | ADDED | SHOWN);
	}
	seen_objects_nr = 0;
}
