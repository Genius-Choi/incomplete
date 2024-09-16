hfs_ext_compare_keys(HFS_INFO * hfs, uint32_t cnid,
    const hfs_btree_key_ext * key)
{
    TSK_FS_INFO *fs = (TSK_FS_INFO *) & (hfs->fs_info);
    uint32_t key_cnid;

    key_cnid = tsk_getu32(fs->endian, key->file_id);
    if (key_cnid < cnid)
        return -1;
    if (key_cnid > cnid)
        return 1;

    /* referring to the same cnids */

    /* we are always looking for the data fork */
    if (key->fork_type != HFS_EXT_KEY_TYPE_DATA)
        return 1;

    /* we are always looking for a start_block of zero
       (interested in the beginning of the extents, regardless
       of what the start_block is); all files except the bad
       blocks file should have a start_block greater than
       zero */
    if (tsk_getu32(fs->endian, key->start_block) == 0)
        return 0;
    return 1;
}
