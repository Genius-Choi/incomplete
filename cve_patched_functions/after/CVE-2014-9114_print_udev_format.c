static void print_udev_format(const char *name, const char *value)
{
	char enc[265], safe[256];
	size_t namelen = strlen(name);

	*safe = *enc = '\0';

	if (!strcmp(name, "TYPE") || !strcmp(name, "VERSION")) {
		blkid_encode_string(value, enc, sizeof(enc));
		printf("ID_FS_%s=%s\n", name, enc);

	} else if (!strcmp(name, "UUID") ||
		 !strcmp(name, "LABEL") ||
		 !strcmp(name, "UUID_SUB")) {

		blkid_safe_string(value, safe, sizeof(safe));
		printf("ID_FS_%s=%s\n", name, safe);

		blkid_encode_string(value, enc, sizeof(enc));
		printf("ID_FS_%s_ENC=%s\n", name, enc);

	} else if (!strcmp(name, "PTUUID")) {
		printf("ID_PART_TABLE_UUID=%s\n", value);

	} else if (!strcmp(name, "PTTYPE")) {
		printf("ID_PART_TABLE_TYPE=%s\n", value);

	} else if (!strcmp(name, "PART_ENTRY_NAME") ||
		  !strcmp(name, "PART_ENTRY_TYPE")) {

		blkid_encode_string(value, enc, sizeof(enc));
		printf("ID_%s=%s\n", name, enc);

	} else if (!strncmp(name, "PART_ENTRY_", 11))
		printf("ID_%s=%s\n", name, value);

	else if (namelen >= 15 && (
		   !strcmp(name + (namelen - 12), "_SECTOR_SIZE") ||
		   !strcmp(name + (namelen - 8), "_IO_SIZE") ||
		   !strcmp(name, "ALIGNMENT_OFFSET")))
			printf("ID_IOLIMIT_%s=%s\n", name, value);
	else
		printf("ID_FS_%s=%s\n", name, value);
}
