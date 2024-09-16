TPM_RC tpm_session_auth_end( SESSION *session )
{
    TPM_RC rval = TPM_RC_SUCCESS;

    DeleteSession( session );

    return rval;
}
