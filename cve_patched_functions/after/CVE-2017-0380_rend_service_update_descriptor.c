rend_service_update_descriptor(rend_service_t *service)
{
  rend_service_descriptor_t *d;
  origin_circuit_t *circ;
  int i;

  rend_service_descriptor_free(service->desc);
  service->desc = NULL;

  d = service->desc = tor_malloc_zero(sizeof(rend_service_descriptor_t));
  d->pk = crypto_pk_dup_key(service->private_key);
  d->timestamp = time(NULL);
  d->timestamp -= d->timestamp % 3600; /* Round down to nearest hour */
  d->intro_nodes = smartlist_new();
  /* Support intro protocols 2 and 3. */
  d->protocols = (1 << 2) + (1 << 3);

  for (i = 0; i < smartlist_len(service->intro_nodes); ++i) {
    rend_intro_point_t *intro_svc = smartlist_get(service->intro_nodes, i);
    rend_intro_point_t *intro_desc;

    /* This intro point won't be listed in the descriptor... */
    intro_svc->listed_in_last_desc = 0;

    circ = find_intro_circuit(intro_svc, service->pk_digest);
    if (!circ || circ->base_.purpose != CIRCUIT_PURPOSE_S_INTRO) {
      /* This intro point's circuit isn't finished yet.  Don't list it. */
      continue;
    }

    /* ...unless this intro point is listed in the descriptor. */
    intro_svc->listed_in_last_desc = 1;

    /* We have an entirely established intro circuit.  Publish it in
     * our descriptor. */
    intro_desc = tor_malloc_zero(sizeof(rend_intro_point_t));
    intro_desc->extend_info = extend_info_dup(intro_svc->extend_info);
    if (intro_svc->intro_key)
      intro_desc->intro_key = crypto_pk_dup_key(intro_svc->intro_key);
    smartlist_add(d->intro_nodes, intro_desc);

    if (intro_svc->time_published == -1) {
      /* We are publishing this intro point in a descriptor for the
       * first time -- note the current time in the service's copy of
       * the intro point. */
      intro_svc->time_published = time(NULL);
    }
  }
}
