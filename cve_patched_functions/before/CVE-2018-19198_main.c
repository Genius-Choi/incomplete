int main() {
	Suite suite;
	suite.add(auto_ptr<Suite>(new UriSuite()));
	suite.add(auto_ptr<Suite>(new FourSuite()));
	suite.add(auto_ptr<Suite>(new VersionSuite()));
	TextOutput output(TextOutput::Verbose);
	return suite.run(output, false) ? 0 : 1;
}
