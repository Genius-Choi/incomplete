thumbnail_done (NautilusDirectory *directory,
                NautilusFile      *file,
                GdkPixbuf         *pixbuf,
                gboolean           tried_original)
{
    const char *thumb_mtime_str;
    time_t thumb_mtime = 0;

    file->details->thumbnail_is_up_to_date = TRUE;
    file->details->thumbnail_tried_original = tried_original;
    if (file->details->thumbnail)
    {
        g_object_unref (file->details->thumbnail);
        file->details->thumbnail = NULL;
    }
    if (file->details->scaled_thumbnail)
    {
        g_object_unref (file->details->scaled_thumbnail);
        file->details->scaled_thumbnail = NULL;
    }

    if (pixbuf)
    {
        if (tried_original)
        {
            thumb_mtime = file->details->mtime;
        }
        else
        {
            thumb_mtime_str = gdk_pixbuf_get_option (pixbuf, "tEXt::Thumb::MTime");
            if (thumb_mtime_str)
            {
                thumb_mtime = atol (thumb_mtime_str);
            }
        }

        if (thumb_mtime == 0 ||
            thumb_mtime == file->details->mtime)
        {
            file->details->thumbnail = g_object_ref (pixbuf);
            file->details->thumbnail_mtime = thumb_mtime;
        }
        else
        {
            g_free (file->details->thumbnail_path);
            file->details->thumbnail_path = NULL;
        }
    }

    nautilus_directory_async_state_changed (directory);
}
