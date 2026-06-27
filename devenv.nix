{
  pkgs,
  lib,
  config,
  inputs,
  ...
}:
{
  # https://devenv.sh/basics/
  # env.GREET = "devenv";
  env = {
    CC = "clang";
    CXX = "clang++";
  };

  # https://devenv.sh/packages/
  packages = with pkgs; [
    git
    gnumake
    clang
    clang-tools
    gtest
    bear # generates compile_commands.json from make
    pkg-config
    gdb
    valgrind
    doxygen
    graphviz
  ];

  # https://devenv.sh/languages/
  # languages.cplusplus.enable = true;

  # https://devenv.sh/processes/
  # processes.dev.exec = "${lib.getExe pkgs.watchexec} -n -- ls -la";

  # https://devenv.sh/services/
  # services.postgres.enable = true;

  # https://devenv.sh/scripts/
  # scripts.hello.exec = ''
  #   echo hello from $GREET
  # '';
  # https://devenv.sh/basics/
  # enterShell = ''
  #   hello         # Run scripts directly
  #   git --version # Use packages
  # '';
  enterShell = ''
    export CC="${pkgs.clang}/bin/clang"
    export CXX="${pkgs.clang}/bin/clang++"
  '';

  # https://devenv.sh/tasks/
  # tasks = {
  #   "myproj:setup".exec = "mytool build";
  #   "devenv:enterShell".after = [ "myproj:setup" ];
  # };

  # https://devenv.sh/tests/
  # enterTest = ''
  #   echo "Running tests"
  #   git --version | grep --color=auto "${pkgs.git.version}"
  # '';
  enterTest = ''
    make test
  '';

  # https://devenv.sh/git-hooks/
  # git-hooks.hooks.shellcheck.enable = true;
  git-hooks.hooks = {
    typos.enable = true;
    clang-format.enable = true;
    clang-tidy.enable = true;
  };

  # See full reference at https://devenv.sh/reference/options/
}
