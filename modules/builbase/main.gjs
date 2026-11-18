import builbase

fn main() {
    builbase::banner("builbase example")
    builbase::step("Checking the package helpers")
    builbase::require(builbase::version() == "0.1.0", "Unexpected package version")
    builbase::success("Build helper package is ready")
}
