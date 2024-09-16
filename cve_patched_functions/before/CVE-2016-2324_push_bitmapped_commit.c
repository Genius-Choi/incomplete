static inline void push_bitmapped_commit(struct commit *commit, struct ewah_bitmap *reused)
{
	if (writer.selected_nr >= writer.selected_alloc) {
		writer.selected_alloc = (writer.selected_alloc + 32) * 2;
		REALLOC_ARRAY(writer.selected, writer.selected_alloc);
	}

	writer.selected[writer.selected_nr].commit = commit;
	writer.selected[writer.selected_nr].bitmap = reused;
	writer.selected[writer.selected_nr].flags = 0;

	writer.selected_nr++;
}
