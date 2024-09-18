proto_register_usb_ms(void)
{
    static hf_register_info hf[] = {
        { &hf_usb_ms_dCBWSignature,
        { "Signature", "usbms.dCBWSignature", FT_UINT32, BASE_HEX,
          NULL, 0x0, NULL, HFILL }},

        { &hf_usb_ms_dCBWTag,
        { "Tag", "usbms.dCBWTag", FT_UINT32, BASE_HEX,
          NULL, 0x0, NULL, HFILL }},

        { &hf_usb_ms_dCBWDataTransferLength,
        { "DataTransferLength", "usbms.dCBWDataTransferLength", FT_UINT32, BASE_DEC,
          NULL, 0x0, NULL, HFILL }},

        { &hf_usb_ms_dCBWFlags,
        { "Flags", "usbms.dCBWFlags", FT_UINT8, BASE_HEX,
          NULL, 0x0, NULL, HFILL }},

        { &hf_usb_ms_dCBWTarget,
        { "Target", "usbms.dCBWTarget", FT_UINT8, BASE_HEX_DEC,
          NULL, 0x70, "Target Number when enabling multi-target mode", HFILL }},

        { &hf_usb_ms_dCBWLUN,
        { "LUN", "usbms.dCBWLUN", FT_UINT8, BASE_HEX,
          NULL, 0x0f, NULL, HFILL }},

        { &hf_usb_ms_dCBWCBLength,
        { "CDB Length", "usbms.dCBWCBLength", FT_UINT8, BASE_HEX,
          NULL, 0x1f, NULL, HFILL }},

        { &hf_usb_ms_dCSWSignature,
        { "Signature", "usbms.dCSWSignature", FT_UINT32, BASE_HEX,
          NULL, 0x0, NULL, HFILL }},

        { &hf_usb_ms_dCSWDataResidue,
        { "DataResidue", "usbms.dCSWDataResidue", FT_UINT32, BASE_DEC,
          NULL, 0x0, NULL, HFILL }},

        { &hf_usb_ms_dCSWStatus,
        { "Status", "usbms.dCSWStatus", FT_UINT8, BASE_HEX,
          VALS(status_vals), 0x0, NULL, HFILL }},

        { &hf_usb_ms_request,
        { "bRequest", "usbms.setup.bRequest", FT_UINT8, BASE_HEX, VALS(setup_request_names_vals), 0x0,
                NULL, HFILL }},

        { &hf_usb_ms_value,
        { "wValue", "usbms.setup.wValue", FT_UINT16, BASE_HEX, NULL, 0x0,
                NULL, HFILL }},

        { &hf_usb_ms_index,
        { "wIndex", "usbms.setup.wIndex", FT_UINT16, BASE_DEC, NULL, 0x0,
                NULL, HFILL }},

        { &hf_usb_ms_length,
        { "wLength", "usbms.setup.wLength", FT_UINT16, BASE_DEC, NULL, 0x0,
                NULL, HFILL }},

        { &hf_usb_ms_maxlun,
        { "Max LUN", "usbms.setup.maxlun", FT_UINT8, BASE_DEC, NULL, 0x0,
                NULL, HFILL }},

    };

    static gint *usb_ms_subtrees[] = {
            &ett_usb_ms,
    };


    proto_usb_ms = proto_register_protocol("USB Mass Storage", "USBMS", "usbms");
    proto_register_field_array(proto_usb_ms, hf, array_length(hf));
    proto_register_subtree_array(usb_ms_subtrees, array_length(usb_ms_subtrees));

    register_dissector("usbms", dissect_usb_ms_bulk, proto_usb_ms);
}
