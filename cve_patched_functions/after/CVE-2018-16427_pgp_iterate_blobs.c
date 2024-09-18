pgp_iterate_blobs(pgp_blob_t *blob, int level, void (*func)())
{
	if (blob) {
		if (level > 0) {
			pgp_blob_t *child = blob->files;

			while (child != NULL) {
				pgp_blob_t *next = child->next;

				pgp_iterate_blobs(child, level-1, func);
				child = next;
			}
		}
		func(blob);
	}
}
