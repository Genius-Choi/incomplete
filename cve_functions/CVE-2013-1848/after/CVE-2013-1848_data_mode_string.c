static char *data_mode_string(unsigned long mode)
{
	switch (mode) {
	case EXT3_MOUNT_JOURNAL_DATA:
		return "journal";
	case EXT3_MOUNT_ORDERED_DATA:
		return "ordered";
	case EXT3_MOUNT_WRITEBACK_DATA:
		return "writeback";
	}
	return "unknown";
}
