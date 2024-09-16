get_default_executable_text_file_action (void)
{
    int preferences_value;

    preferences_value = g_settings_get_enum (nautilus_preferences,
                                             NAUTILUS_PREFERENCES_EXECUTABLE_TEXT_ACTIVATION);
    switch (preferences_value)
    {
        case NAUTILUS_EXECUTABLE_TEXT_LAUNCH:
        {
            return ACTIVATION_ACTION_LAUNCH;
        }

        case NAUTILUS_EXECUTABLE_TEXT_DISPLAY:
        {
            return ACTIVATION_ACTION_OPEN_IN_APPLICATION;
        }

        case NAUTILUS_EXECUTABLE_TEXT_ASK:
        default:
            return ACTIVATION_ACTION_ASK;
    }
}
