rend_service_add_ephemeral(crypto_pk_t *pk,
                           smartlist_t *ports,
                           int max_streams_per_circuit,
                           int max_streams_close_circuit,
                           rend_auth_type_t auth_type,
                           smartlist_t *auth_clients,
                           char **service_id_out)
{
  *service_id_out = NULL;
  /* Allocate the service structure, and initialize the key, and key derived
   * parameters.
   */
  rend_service_t *s = tor_malloc_zero(sizeof(rend_service_t));
  s->directory = NULL; /* This indicates the service is ephemeral. */
  s->private_key = pk;
  s->auth_type = auth_type;
  s->clients = auth_clients;
  s->ports = ports;
  s->intro_period_started = time(NULL);
  s->n_intro_points_wanted = NUM_INTRO_POINTS_DEFAULT;
  s->max_streams_per_circuit = max_streams_per_circuit;
  s->max_streams_close_circuit = max_streams_close_circuit;
  if (rend_service_derive_key_digests(s) < 0) {
    rend_service_free(s);
    return RSAE_BADPRIVKEY;
  }

  if (!s->ports || smartlist_len(s->ports) == 0) {
    log_warn(LD_CONFIG, "At least one VIRTPORT/TARGET must be specified.");
    rend_service_free(s);
    return RSAE_BADVIRTPORT;
  }
  if (s->auth_type != REND_NO_AUTH &&
      (!s->clients || smartlist_len(s->clients) == 0)) {
    log_warn(LD_CONFIG, "At least one authorized client must be specified.");
    rend_service_free(s);
    return RSAE_BADAUTH;
  }

  /* Enforcing pk/id uniqueness should be done by rend_service_load_keys(), but
   * it's not, see #14828.
   */
  if (rend_service_get_by_pk_digest(s->pk_digest)) {
    log_warn(LD_CONFIG, "Onion Service private key collides with an "
             "existing service.");
    rend_service_free(s);
    return RSAE_ADDREXISTS;
  }
  if (rend_service_get_by_service_id(s->service_id)) {
    log_warn(LD_CONFIG, "Onion Service id collides with an existing service.");
    rend_service_free(s);
    return RSAE_ADDREXISTS;
  }

  /* Initialize the service. */
  if (rend_add_service(NULL, s)) {
    return RSAE_INTERNAL;
  }
  *service_id_out = tor_strdup(s->service_id);

  log_debug(LD_CONFIG, "Added ephemeral Onion Service: %s", s->service_id);
  return RSAE_OKAY;
}
