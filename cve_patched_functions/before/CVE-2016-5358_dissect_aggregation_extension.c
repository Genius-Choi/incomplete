dissect_aggregation_extension(tvbuff_t *tvb, packet_info *pinfo _U_, proto_tree *tree, int offset, int data_len)
{
    proto_tree *ftree;
    ptvcursor_t *csr;

    ftree = proto_tree_add_subtree(tree, tvb, offset, data_len, ett_aggregation_extension, NULL, "Aggregation Extension");
    add_ppi_field_header(tvb, ftree, &offset);
    data_len -= 4; /* Subtract field header length */

    if (data_len != PPI_AGGREGATION_EXTENSION_LEN) {
        proto_tree_add_expert_format(ftree, pinfo, &ei_ppi_invalid_length, tvb, offset, data_len, "Invalid length: %u", data_len);
        THROW(ReportedBoundsError);
    }

    csr = ptvcursor_new(ftree, tvb, offset);

    ptvcursor_add(csr, hf_aggregation_extension_interface_id, 4, ENC_LITTLE_ENDIAN); /* Last */
    ptvcursor_free(csr);
}
