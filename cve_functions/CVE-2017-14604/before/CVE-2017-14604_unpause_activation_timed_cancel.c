unpause_activation_timed_cancel (ActivateParameters *parameters)
{
    if (!parameters->timed_wait_active)
    {
        activation_start_timed_cancel (parameters);
    }
}
