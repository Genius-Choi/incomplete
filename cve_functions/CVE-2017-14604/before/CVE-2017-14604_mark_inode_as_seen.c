mark_inode_as_seen (DeepCountState *state,
                    GFileInfo      *info)
{
    guint64 inode;

    inode = g_file_info_get_attribute_uint64 (info, G_FILE_ATTRIBUTE_UNIX_INODE);
    if (inode != 0)
    {
        g_array_append_val (state->seen_deep_count_inodes, inode);
    }
}
