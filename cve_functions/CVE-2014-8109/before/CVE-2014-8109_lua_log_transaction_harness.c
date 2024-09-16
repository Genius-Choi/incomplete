static int lua_log_transaction_harness(request_rec *r)
{
    return lua_request_rec_hook_harness(r, "log_transaction", APR_HOOK_FIRST);
}
