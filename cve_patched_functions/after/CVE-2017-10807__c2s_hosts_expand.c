static void _c2s_hosts_expand(c2s_t c2s)
{
    char *realm;
    config_elem_t elem;
    char id[1024];
    int i;

    elem = config_get(c2s->config, "local.id");
    if(!elem) {
        log_write(c2s->log, LOG_NOTICE, "no local.id configured - skipping local domains configuration");
        return;
    }
    for(i = 0; i < elem->nvalues; i++) {
        host_t host = (host_t) pmalloco(xhash_pool(c2s->hosts), sizeof(struct host_st));
        if(!host) {
            log_write(c2s->log, LOG_ERR, "cannot allocate memory for new host, aborting");
            exit(1);
        }

        realm = j_attr((const char **) elem->attrs[i], "realm");

        /* stringprep ids (domain names) so that they are in canonical form */
        strncpy(id, elem->values[i], 1024);
        id[1023] = '\0';
        if (stringprep_nameprep(id, 1024) != 0) {
            log_write(c2s->log, LOG_ERR, "cannot stringprep id %s, aborting", id);
            exit(1);
        }

        host->realm = (realm != NULL) ? realm : pstrdup(xhash_pool(c2s->hosts), id);

        host->host_pemfile = j_attr((const char **) elem->attrs[i], "pemfile");

        host->host_cachain = j_attr((const char **) elem->attrs[i], "cachain");

        host->host_verify_mode = j_atoi(j_attr((const char **) elem->attrs[i], "verify-mode"), 0);

        host->host_private_key_password = j_attr((const char **) elem->attrs[i], "private-key-password");

        host->host_ciphers = j_attr((const char **) elem->attrs[i], "ciphers");

#ifdef HAVE_SSL
        if(host->host_pemfile != NULL) {
            if(c2s->sx_ssl == NULL) {
                c2s->sx_ssl = sx_env_plugin(c2s->sx_env, sx_ssl_init, host->realm, host->host_pemfile, host->host_cachain, host->host_verify_mode, host->host_private_key_password, host->host_ciphers);
                if(c2s->sx_ssl == NULL) {
                    log_write(c2s->log, LOG_ERR, "failed to load %s SSL pemfile", host->realm);
                    host->host_pemfile = NULL;
                }
            } else {
                if(sx_ssl_server_addcert(c2s->sx_ssl, host->realm, host->host_pemfile, host->host_cachain, host->host_verify_mode, host->host_private_key_password, host->host_ciphers) != 0) {
                    log_write(c2s->log, LOG_ERR, "failed to load %s SSL pemfile", host->realm);
                    host->host_pemfile = NULL;
                }
            }
        }
#endif

        host->host_require_starttls = (j_attr((const char **) elem->attrs[i], "require-starttls") != NULL);

        host->ar_module_name = j_attr((const char **) elem->attrs[i], "authreg-module");
        if(host->ar_module_name) {
            if((host->ar = authreg_init(c2s, host->ar_module_name)) == NULL) {
                log_write(c2s->log, LOG_NOTICE, "failed to load %s authreg module - using default", host->realm);
                host->ar = c2s->ar;
            }
        } else
            host->ar = c2s->ar;

        host->ar_register_enable = (j_attr((const char **) elem->attrs[i], "register-enable") != NULL);
        host->ar_register_oob = j_attr((const char **) elem->attrs[i], "register-oob");
        if(host->ar_register_enable || host->ar_register_oob) {
            host->ar_register_instructions = j_attr((const char **) elem->attrs[i], "instructions");
            if(host->ar_register_instructions == NULL) {
                if(host->ar_register_oob)
                    host->ar_register_instructions = "Only web based registration is possible with this server.";
                else
                    host->ar_register_instructions = "Enter a username and password to register with this server.";
            }
        } else
            host->ar_register_password = (j_attr((const char **) elem->attrs[i], "password-change") != NULL);

        /* check for empty <id/> CDATA - XXX this "1" is VERY config.c dependant !!! */
        if(! strcmp(id, "1")) {
            /* remove the realm even if set */
            host->realm = NULL;

            /* skip if vHost already configured */
            if(! c2s->vhost)
                c2s->vhost = host;

            /* add meaningful log "id" */
            strcpy(id, "default vHost");
        } else {
            /* insert into vHosts xhash */
            xhash_put(c2s->hosts, pstrdup(xhash_pool(c2s->hosts), id), host);
        }

        log_write(c2s->log, LOG_NOTICE, "[%s] configured; realm=%s, authreg=%s, registration %s, using PEM:%s",
                  id, (host->realm != NULL ? host->realm : "no realm set"),
                  (host->ar_module_name ? host->ar_module_name : c2s->ar_module_name),
                  (host->ar_register_enable ? "enabled" : "disabled"),
                  (host->host_pemfile ? host->host_pemfile : "Default"));
    }
}
