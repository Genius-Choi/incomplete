uint32_t next_cluster(DOS_FS * fs, uint32_t cluster)
{
    uint32_t value;
    FAT_ENTRY curEntry;

    get_fat(&curEntry, fs->fat, cluster, fs);

    value = curEntry.value;
    if (FAT_IS_BAD(fs, value))
	die("Internal error: next_cluster on bad cluster");
    return FAT_IS_EOF(fs, value) ? -1 : value;
}
