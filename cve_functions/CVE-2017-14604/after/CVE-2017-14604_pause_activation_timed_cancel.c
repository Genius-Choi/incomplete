pause_activation_timed_cancel (ActivateParameters *parameters)
{
    if (parameters->timed_wait_active)
    {
        eel_timed_wait_stop (cancel_activate_callback, parameters);
        parameters->timed_wait_active = FALSE;
    }
}
