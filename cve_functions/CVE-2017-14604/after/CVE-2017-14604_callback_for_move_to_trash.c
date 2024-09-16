callback_for_move_to_trash (GHashTable      *debuting_uris,
                            gboolean         user_cancelled,
                            MoveTrashCBData *data)
{
    if (data->real_callback)
    {
        data->real_callback (debuting_uris, !user_cancelled, data->real_data);
    }
    g_slice_free (MoveTrashCBData, data);
}
