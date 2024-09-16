read_PackInfo(struct archive_read *a, struct _7z_pack_info *pi)
{
	const unsigned char *p;
	unsigned i;

	memset(pi, 0, sizeof(*pi));

	/*
	 * Read PackPos.
	 */
	if (parse_7zip_uint64(a, &(pi->pos)) < 0)
		return (-1);

	/*
	 * Read NumPackStreams.
	 */
	if (parse_7zip_uint64(a, &(pi->numPackStreams)) < 0)
		return (-1);
	if (pi->numPackStreams == 0)
		return (-1);
	if (UMAX_ENTRY < pi->numPackStreams)
		return (-1);

	/*
	 * Read PackSizes[num]
	 */
	if ((p = header_bytes(a, 1)) == NULL)
		return (-1);
	if (*p == kEnd)
		/* PackSizes[num] are not present. */
		return (0);
	if (*p != kSize)
		return (-1);
	pi->sizes = calloc((size_t)pi->numPackStreams, sizeof(uint64_t));
	pi->positions = calloc((size_t)pi->numPackStreams, sizeof(uint64_t));
	if (pi->sizes == NULL || pi->positions == NULL)
		return (-1);

	for (i = 0; i < pi->numPackStreams; i++) {
		if (parse_7zip_uint64(a, &(pi->sizes[i])) < 0)
			return (-1);
	}

	/*
	 * Read PackStreamDigests[num]
	 */
	if ((p = header_bytes(a, 1)) == NULL)
		return (-1);
	if (*p == kEnd) {
		/* PackStreamDigests[num] are not present. */
		pi->digest.defineds =
		    calloc((size_t)pi->numPackStreams, sizeof(*pi->digest.defineds));
		pi->digest.digests =
		    calloc((size_t)pi->numPackStreams, sizeof(*pi->digest.digests));
		if (pi->digest.defineds == NULL || pi->digest.digests == NULL)
			return (-1);
		return (0);
	}

	if (*p != kSize)
		return (-1);

	if (read_Digests(a, &(pi->digest), (size_t)pi->numPackStreams) < 0)
		return (-1);

	/*
	 *  Must be marked by kEnd.
	 */
	if ((p = header_bytes(a, 1)) == NULL)
		return (-1);
	if (*p != kEnd)
		return (-1);
	return (0);
}
