seen_inode (DeepCountState *state,
            GFileInfo      *info)
{
    guint64 inode, inode2;
    guint i;

    inode = g_file_info_get_attribute_uint64 (info, G_FILE_ATTRIBUTE_UNIX_INODE);

    if (inode != 0)
    {
        for (i = 0; i < state->seen_deep_count_inodes->len; i++)
        {
            inode2 = g_array_index (state->seen_deep_count_inodes, guint64, i);
            if (inode == inode2)
            {
                return TRUE;
            }
        }
    }

    return FALSE;
}
