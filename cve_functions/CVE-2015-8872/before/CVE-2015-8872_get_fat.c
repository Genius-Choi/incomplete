void get_fat(FAT_ENTRY * entry, void *fat, uint32_t cluster, DOS_FS * fs)
{
    unsigned char *ptr;

    switch (fs->fat_bits) {
    case 12:
	ptr = &((unsigned char *)fat)[cluster * 3 / 2];
	entry->value = 0xfff & (cluster & 1 ? (ptr[0] >> 4) | (ptr[1] << 4) :
				(ptr[0] | ptr[1] << 8));
	break;
    case 16:
	entry->value = le16toh(((unsigned short *)fat)[cluster]);
	break;
    case 32:
	/* According to M$, the high 4 bits of a FAT32 entry are reserved and
	 * are not part of the cluster number. So we cut them off. */
	{
	    uint32_t e = le32toh(((unsigned int *)fat)[cluster]);
	    entry->value = e & 0xfffffff;
	    entry->reserved = e >> 28;
	}
	break;
    default:
	die("Bad FAT entry size: %d bits.", fs->fat_bits);
    }
}
