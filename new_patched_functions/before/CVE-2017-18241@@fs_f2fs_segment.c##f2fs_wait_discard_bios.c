void f2fs_wait_discard_bios(struct f2fs_sb_info *sbi)
{
	__issue_discard_cmd(sbi, false);
	__wait_discard_cmd(sbi, false);
}
