bool AutoParallel::NotSharedNode(const string& name) {
  return shared_nodes_.find(name) == shared_nodes_.end();
}
