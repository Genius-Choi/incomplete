proto_reg_handoff_usb_audio(void)
{
    dissector_handle_t usb_audio_bulk_handle, usb_audio_descr_handle;

    usb_audio_descr_handle = create_dissector_handle(
            dissect_usb_audio_descriptor, proto_usb_audio);
    dissector_add_uint("usb.descriptor", IF_CLASS_AUDIO, usb_audio_descr_handle);

    usb_audio_bulk_handle = find_dissector("usbaudio");
    dissector_add_uint("usb.bulk", IF_CLASS_AUDIO, usb_audio_bulk_handle);

    sysex_handle = find_dissector_add_dependency("sysex", proto_usb_audio);
}
