bmap_to_share_mode(unsigned long bmap) {
	int i;
	unsigned int access = 0;

	for (i = 1; i < 4; i++) {
		if (test_bit(i, &bmap))
			access |= i;
	}
	return access;
}
