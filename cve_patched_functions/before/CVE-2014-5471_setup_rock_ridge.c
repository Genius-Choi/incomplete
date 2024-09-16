static void setup_rock_ridge(struct iso_directory_record *de,
			struct inode *inode, struct rock_state *rs)
{
	rs->len = sizeof(struct iso_directory_record) + de->name_len[0];
	if (rs->len & 1)
		(rs->len)++;
	rs->chr = (unsigned char *)de + rs->len;
	rs->len = *((unsigned char *)de) - rs->len;
	if (rs->len < 0)
		rs->len = 0;

	if (ISOFS_SB(inode->i_sb)->s_rock_offset != -1) {
		rs->len -= ISOFS_SB(inode->i_sb)->s_rock_offset;
		rs->chr += ISOFS_SB(inode->i_sb)->s_rock_offset;
		if (rs->len < 0)
			rs->len = 0;
	}
}
