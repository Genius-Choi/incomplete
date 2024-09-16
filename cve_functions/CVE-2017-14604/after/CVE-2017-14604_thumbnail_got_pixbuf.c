thumbnail_got_pixbuf (NautilusDirectory *directory,
                      NautilusFile      *file,
                      GdkPixbuf         *pixbuf,
                      gboolean           tried_original)
{
    nautilus_directory_ref (directory);

    nautilus_file_ref (file);
    thumbnail_done (directory, file, pixbuf, tried_original);
    nautilus_file_changed (file);
    nautilus_file_unref (file);

    if (pixbuf)
    {
        g_object_unref (pixbuf);
    }

    nautilus_directory_unref (directory);
}
