should_confirm_trash (void)
{
    GSettings *prefs;
    gboolean confirm_trash;

    prefs = g_settings_new ("org.gnome.nautilus.preferences");
    confirm_trash = g_settings_get_boolean (prefs, NAUTILUS_PREFERENCES_CONFIRM_TRASH);
    g_object_unref (prefs);
    return confirm_trash;
}
