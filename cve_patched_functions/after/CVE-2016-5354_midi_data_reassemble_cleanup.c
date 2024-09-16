midi_data_reassemble_cleanup(void)
{
    reassembly_table_destroy(&midi_data_reassembly_table);
}
