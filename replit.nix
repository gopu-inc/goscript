{pkgs}: {
  deps = [
    pkgs.sqlite
    pkgs.pkg-config
    pkgs.libffi
    pkgs.bison
    pkgs.flex
  ];
}
