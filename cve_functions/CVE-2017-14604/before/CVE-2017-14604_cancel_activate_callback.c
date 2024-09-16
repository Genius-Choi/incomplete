cancel_activate_callback (gpointer callback_data)
{
    ActivateParameters *parameters = callback_data;

    parameters->timed_wait_active = FALSE;

    g_cancellable_cancel (parameters->cancellable);

    if (parameters->files_handle)
    {
        nautilus_file_list_cancel_call_when_ready (parameters->files_handle);
        parameters->files_handle = NULL;
        activation_parameters_free (parameters);
    }
}
