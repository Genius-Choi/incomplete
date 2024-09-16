proto_reg_handoff_usb_ms(void)
{
    dissector_handle_t usb_ms_bulk_handle;
    dissector_handle_t usb_ms_control_handle;

    usb_ms_bulk_handle = find_dissector("usbms");
    dissector_add_uint("usb.bulk", IF_CLASS_MASS_STORAGE, usb_ms_bulk_handle);

    usb_ms_control_handle = create_dissector_handle(dissect_usb_ms_control, proto_usb_ms);
    dissector_add_uint("usb.control", IF_CLASS_MASS_STORAGE, usb_ms_control_handle);

    heur_dissector_add("usb.bulk", dissect_usb_ms_bulk_heur, "Mass Storage USB bulk endpoint", "ms_usb_bulk", proto_usb_ms, HEURISTIC_ENABLE);
}
