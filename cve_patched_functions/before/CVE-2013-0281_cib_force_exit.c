cib_force_exit(gpointer data)
{
    crm_notice("Forcing exit!");
    terminate_cib(__FUNCTION__, TRUE);
    return FALSE;
}
