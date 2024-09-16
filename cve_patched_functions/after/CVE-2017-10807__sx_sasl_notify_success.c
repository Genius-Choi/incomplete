static void _sx_sasl_notify_success(sx_t s, void *arg) {
    sx_plugin_t p = (sx_plugin_t) arg;

    _sx_chain_io_plugin(s, p);
    _sx_debug(ZONE, "auth completed, resetting");

    _sx_reset(s);

    sx_server_init(s, s->flags);
}
