dissect_u3v_register_bases(guint64 addr, tvbuff_t *tvb, gint offset, u3v_conv_info_t * u3v_conv_info)
{
    if ( addr < 0x10000 ) {
        switch (addr) {
        case U3V_ABRM_SBRM_ADDRESS:
            u3v_conv_info->sbrm_addr = tvb_get_letoh64(tvb, offset);
            break;
        case U3V_ABRM_MANIFEST_TABLE_ADDRESS:
            u3v_conv_info->manifest_addr = tvb_get_letoh64(tvb, offset);
            break;
        }
    }
    if ( u3v_conv_info->sbrm_addr != 0 &&  (addr >= u3v_conv_info->sbrm_addr)) {
        addr -= u3v_conv_info->sbrm_addr;
        switch(addr) {
        case U3V_SBRM_SIRM_ADDRESS:
            u3v_conv_info->sirm_addr = tvb_get_letoh64(tvb, offset);
            break;
        case U3V_SBRM_EIRM_ADDRESS:
            u3v_conv_info->eirm_addr = tvb_get_letoh64(tvb, offset);
            break;
        case U3V_SBRM_IIDC2_ADDRESS:
            u3v_conv_info->iidc2_addr = tvb_get_letoh64(tvb, offset);
            break;
        }
    }
}
