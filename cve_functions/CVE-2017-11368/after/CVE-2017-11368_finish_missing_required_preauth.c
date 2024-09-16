finish_missing_required_preauth(void *arg)
{
    struct as_req_state *state = (struct as_req_state *)arg;

    finish_process_as_req(state, state->preauth_err);
}
