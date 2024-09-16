cib_ccm_msg_callback(oc_ed_t event, void *cookie, size_t size, const void *data)
{
    gboolean update_id = FALSE;
    const oc_ev_membership_t *membership = data;

    CRM_ASSERT(membership != NULL);

    crm_info("Processing CCM event=%s (id=%d)", ccm_event_name(event), membership->m_instance);

    if (current_instance > membership->m_instance) {
        crm_err("Membership instance ID went backwards! %d->%d",
                current_instance, membership->m_instance);
        CRM_ASSERT(current_instance <= membership->m_instance);
    }

    switch (event) {
        case OC_EV_MS_NEW_MEMBERSHIP:
        case OC_EV_MS_INVALID:
            update_id = TRUE;
            break;
        case OC_EV_MS_PRIMARY_RESTORED:
            update_id = TRUE;
            break;
        case OC_EV_MS_NOT_PRIMARY:
            crm_trace("Ignoring transitional CCM event: %s", ccm_event_name(event));
            break;
        case OC_EV_MS_EVICTED:
            crm_err("Evicted from CCM: %s", ccm_event_name(event));
            break;
        default:
            crm_err("Unknown CCM event: %d", event);
    }

    if (update_id) {
        unsigned int lpc = 0;

        CRM_CHECK(membership != NULL, return);

        current_instance = membership->m_instance;

        for (lpc = 0; lpc < membership->m_n_out; lpc++) {
            crm_update_ccm_node(membership, lpc + membership->m_out_idx, CRM_NODE_LOST,
                                current_instance);
        }

        for (lpc = 0; lpc < membership->m_n_member; lpc++) {
            crm_update_ccm_node(membership, lpc + membership->m_memb_idx, CRM_NODE_ACTIVE,
                                current_instance);
        }
    }

    if (ccm_api_callback_done == NULL) {
        ccm_api_callback_done =
            find_library_function(&ccm_library, CCM_LIBRARY, "oc_ev_callback_done", 1);
    }
    (*ccm_api_callback_done) (cookie);
    return;
}
