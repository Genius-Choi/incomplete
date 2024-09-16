midi_data_reassemble_init(void)
{
    reassembly_table_init(&midi_data_reassembly_table,
                          &addresses_reassembly_table_functions);
}
