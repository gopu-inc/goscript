import builbase

fn main() {
    builbase::banner("builbase example")
    builbase::step("Checking the package helpers")
    if (builbase::require(builbase::version() == "0.1.1", "Unexpected package version")) {
        builbase::success("Build helper package is ready")
    }
}
