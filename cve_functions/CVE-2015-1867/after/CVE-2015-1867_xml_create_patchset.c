xml_create_patchset(int format, xmlNode *source, xmlNode *target, bool *config_changed, bool manage_version, bool with_digest)
{
    int counter = 0;
    bool config = FALSE;
    xmlNode *patch = NULL;
    const char *version = crm_element_value(source, XML_ATTR_CRM_VERSION);

    xml_acl_disable(target);
    if(xml_document_dirty(target) == FALSE) {
        crm_trace("No change %d", format);
        return NULL; /* No change */
    }

    config = is_config_change(target);
    if(config_changed) {
        *config_changed = config;
    }

    if(manage_version && config) {
        crm_trace("Config changed %d", format);
        crm_xml_add(target, XML_ATTR_NUMUPDATES, "0");

        crm_element_value_int(target, XML_ATTR_GENERATION, &counter);
        crm_xml_add_int(target, XML_ATTR_GENERATION, counter+1);

    } else if(manage_version) {
        crm_trace("Status changed %d", format);
        crm_element_value_int(target, XML_ATTR_NUMUPDATES, &counter);
        crm_xml_add_int(target, XML_ATTR_NUMUPDATES, counter+1);
    }

    if(format == 0) {
        if(patch_legacy_mode()) {
            format = 1;

        } else if(compare_version("3.0.8", version) < 0) {
            format = 2;

        } else {
            format = 1;
        }
        crm_trace("Using patch format %d for version: %s", format, version);
    }

    switch(format) {
        case 1:
            with_digest = TRUE;
            patch = xml_create_patchset_v1(source, target, config, with_digest);
            break;
        case 2:
            patch = xml_create_patchset_v2(source, target);
            break;
        default:
            crm_err("Unknown patch format: %d", format);
            return NULL;
    }

    if(patch && with_digest) {
        char *digest = calculate_xml_versioned_digest(target, FALSE, TRUE, version);

        crm_xml_add(patch, XML_ATTR_DIGEST, digest);
        free(digest);
    }
    return patch;
}
