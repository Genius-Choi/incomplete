activation_start_timed_cancel (ActivateParameters *parameters)
{
    parameters->timed_wait_active = TRUE;
    eel_timed_wait_start_with_duration
        (DELAY_UNTIL_CANCEL_MSECS,
        cancel_activate_callback,
        parameters,
        parameters->timed_wait_prompt,
        parameters->parent_window);
}
