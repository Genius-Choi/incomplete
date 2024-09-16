nautilus_mime_file_opens_in_external_app (NautilusFile *file)
{
    ActivationAction activation_action;

    activation_action = get_activation_action (file);

    return (activation_action == ACTIVATION_ACTION_OPEN_IN_APPLICATION);
}
