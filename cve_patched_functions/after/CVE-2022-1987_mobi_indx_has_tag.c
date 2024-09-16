bool mobi_indx_has_tag(const MOBIIndx *indx, const size_t tagid) {
    if (indx) {
        for (size_t i = 0; i < indx->entries_count; i++) {
            MOBIIndexEntry entry = indx->entries[i];
            for(size_t j = 0; j < entry.tags_count; j++) {
                if (entry.tags[j].tagid == tagid) {
                    return true;
                }
            }
        }
    }
    return false;
}
