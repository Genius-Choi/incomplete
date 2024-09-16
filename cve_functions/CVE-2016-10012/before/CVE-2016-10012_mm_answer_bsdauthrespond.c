mm_answer_bsdauthrespond(int sock, Buffer *m)
{
	char *response;
	int authok;

	if (!options.kbd_interactive_authentication)
		fatal("%s: kbd-int authentication not enabled", __func__);
	if (authctxt->as == NULL)
		fatal("%s: no bsd auth session", __func__);

	response = buffer_get_string(m, NULL);
	authok = options.challenge_response_authentication &&
	    auth_userresponse(authctxt->as, response, 0);
	authctxt->as = NULL;
	debug3("%s: <%s> = <%d>", __func__, response, authok);
	free(response);

	buffer_clear(m);
	buffer_put_int(m, authok);

	debug3("%s: sending authenticated: %d", __func__, authok);
	mm_request_send(sock, MONITOR_ANS_BSDAUTHRESPOND, m);

	auth_method = "keyboard-interactive";
	auth_submethod = "bsdauth";

	return (authok != 0);
}
