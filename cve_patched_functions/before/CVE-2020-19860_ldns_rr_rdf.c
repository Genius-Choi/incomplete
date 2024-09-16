ldns_rr_rdf(const ldns_rr *rr, size_t nr)
{
	if (rr && nr < ldns_rr_rd_count(rr)) {
		return rr->_rdata_fields[nr];
	} else {
		return NULL;
	}
}
