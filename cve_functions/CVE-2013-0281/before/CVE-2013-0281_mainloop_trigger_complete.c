mainloop_trigger_complete(crm_trigger_t *trig) 
{
    crm_trace("Trigger handler %p complete", trig);
    trig->running = FALSE;
}
