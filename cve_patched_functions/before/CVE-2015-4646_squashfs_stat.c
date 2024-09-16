void squashfs_stat(char *source)
{
	time_t mkfs_time = (time_t) sBlk.s.mkfs_time;
	char *mkfs_str = ctime(&mkfs_time);

#if __BYTE_ORDER == __BIG_ENDIAN
	printf("Found a valid %sSQUASHFS %d:%d superblock on %s.\n",
		sBlk.s.s_major == 4 ? "" : swap ? "little endian " :
		"big endian ", sBlk.s.s_major, sBlk.s.s_minor, source);
#else
	printf("Found a valid %sSQUASHFS %d:%d superblock on %s.\n",
		sBlk.s.s_major == 4 ? "" : swap ? "big endian " :
		"little endian ", sBlk.s.s_major, sBlk.s.s_minor, source);
#endif

	printf("Creation or last append time %s", mkfs_str ? mkfs_str :
		"failed to get time\n");
	printf("Filesystem size %llu bytes (%.2f Kbytes / %.2f Mbytes)\n",
		sBlk.s.bytes_used, sBlk.s.bytes_used / 1024.0,
		sBlk.s.bytes_used / (1024.0 * 1024.0));

	if(sBlk.s.s_major == 4) {
		printf("Compression %s\n", comp->name);

		if(SQUASHFS_COMP_OPTS(sBlk.s.flags)) {
			char buffer[SQUASHFS_METADATA_SIZE] __attribute__ ((aligned));
			int bytes;

			if(!comp->supported)
				printf("\tCould not display compressor options, because %s compression is not supported\n",
						comp->name);
			else {
				bytes = read_block(fd, sizeof(sBlk.s), NULL, 0, buffer);
				if(bytes == 0) {
					ERROR("Failed to read compressor options\n");
					return;
				}

				compressor_display_options(comp, buffer, bytes);
			}
		}
	}

	printf("Block size %d\n", sBlk.s.block_size);
	printf("Filesystem is %sexportable via NFS\n",
		SQUASHFS_EXPORTABLE(sBlk.s.flags) ? "" : "not ");
	printf("Inodes are %scompressed\n",
		SQUASHFS_UNCOMPRESSED_INODES(sBlk.s.flags) ? "un" : "");
	printf("Data is %scompressed\n",
		SQUASHFS_UNCOMPRESSED_DATA(sBlk.s.flags) ? "un" : "");

	if(sBlk.s.s_major >= 4)
		printf("Uids/Gids (Id table) are %scompressed\n",
			SQUASHFS_UNCOMPRESSED_INODES(sBlk.s.flags) ||
			SQUASHFS_UNCOMPRESSED_IDS(sBlk.s.flags) ? "un" : "");

	if(sBlk.s.s_major > 1) {
		if(SQUASHFS_NO_FRAGMENTS(sBlk.s.flags))
			printf("Fragments are not stored\n");
		else {
			printf("Fragments are %scompressed\n",
				SQUASHFS_UNCOMPRESSED_FRAGMENTS(sBlk.s.flags) ?
				"un" : "");
			printf("Always-use-fragments option is %sspecified\n",
				SQUASHFS_ALWAYS_FRAGMENTS(sBlk.s.flags) ? "" :
				"not ");
		}
	}

	if(sBlk.s.s_major == 4) {
		if(SQUASHFS_NO_XATTRS(sBlk.s.flags))
			printf("Xattrs are not stored\n");
		else
			printf("Xattrs are %scompressed\n",
				SQUASHFS_UNCOMPRESSED_XATTRS(sBlk.s.flags) ?
				"un" : "");
	}

	if(sBlk.s.s_major < 4)
			printf("Check data is %spresent in the filesystem\n",
				SQUASHFS_CHECK_DATA(sBlk.s.flags) ? "" :
				"not ");

	if(sBlk.s.s_major > 1)
		printf("Duplicates are %sremoved\n",
			SQUASHFS_DUPLICATES(sBlk.s.flags) ? "" : "not ");
	else
		printf("Duplicates are removed\n");

	if(sBlk.s.s_major > 1)
		printf("Number of fragments %d\n", sBlk.s.fragments);

	printf("Number of inodes %d\n", sBlk.s.inodes);

	if(sBlk.s.s_major == 4)
		printf("Number of ids %d\n", sBlk.s.no_ids);
	else {
		printf("Number of uids %d\n", sBlk.no_uids);
		printf("Number of gids %d\n", sBlk.no_guids);
	}

	TRACE("sBlk.s.inode_table_start 0x%llx\n", sBlk.s.inode_table_start);
	TRACE("sBlk.s.directory_table_start 0x%llx\n",
		sBlk.s.directory_table_start);

	if(sBlk.s.s_major > 1)
		TRACE("sBlk.s.fragment_table_start 0x%llx\n\n",
			sBlk.s.fragment_table_start);

	if(sBlk.s.s_major > 2)
		TRACE("sBlk.s.lookup_table_start 0x%llx\n\n",
			sBlk.s.lookup_table_start);

	if(sBlk.s.s_major == 4) {
		TRACE("sBlk.s.id_table_start 0x%llx\n", sBlk.s.id_table_start);
		TRACE("sBlk.s.xattr_id_table_start 0x%llx\n",
			sBlk.s.xattr_id_table_start);
	} else {
		TRACE("sBlk.uid_start 0x%llx\n", sBlk.uid_start);
		TRACE("sBlk.guid_start 0x%llx\n", sBlk.guid_start);
	}
}
