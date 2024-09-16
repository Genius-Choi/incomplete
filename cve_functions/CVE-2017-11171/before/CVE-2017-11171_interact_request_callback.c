interact_request_callback (SmsConn   conn,
                           SmPointer manager_data,
                           int       dialog_type)
{
        GsmXSMPClient *client = manager_data;
#if 0
        gboolean       res;
        GError        *error;
#endif

        g_debug ("GsmXSMPClient: Client '%s' received InteractRequest(%s)",
                 client->priv->description,
                 dialog_type == SmDialogNormal ? "Dialog" : "Errors");

        gsm_client_end_session_response (GSM_CLIENT (client),
                                         FALSE, FALSE, FALSE,
                                         _("This program is blocking log out."));

#if 0
        /* Can't just call back with Interact because session client
           grabs the keyboard!  So, we try to get it to release
           grabs by telling it we've cancelled the shutdown.
           This grabbing is clearly bullshit and is not supported by
           the client spec or protocol spec.
        */
        res = xsmp_cancel_end_session (GSM_CLIENT (client), &error);
        if (! res) {
                g_warning ("Unable to cancel end session: %s", error->message);
                g_error_free (error);
        }
#endif
        xsmp_interact (GSM_CLIENT (client));
}
