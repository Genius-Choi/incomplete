void AutoParallel::BuildGraph(GraphDef* graph) {
  AddSharedNodes(graph);
  for (int i = 0; i < num_replicas_; i++) {
    AddOneReplica(graph, i);
  }
  std::set<string> fetches;
  for (size_t i = 0; i < item_->fetch.size(); i++) {
    for (int j = 0; j < num_replicas_; j++) {
      string prefix = strings::StrCat(kAutoParallelPrefix, "-Replica-", j);
      string fetch = AddPrefixToNodeName(item_->fetch[i], prefix);
      fetches.insert(fetch);
    }
  }
  string name_control =
      strings::StrCat(kAutoParallelPrefix, "-Control-", "Fetch");
  auto control = AddNodeControl(name_control, fetches, graph);

  for (const auto& fetch : item_->fetch) {
    AddNodeControl(fetch, {control->name()}, graph);
  }
  *graph->mutable_library() = item_->graph.library();
  *graph->mutable_versions() = item_->graph.versions();
  LOG(INFO) << "Parallelized graph size: " << graph->node_size();
}
