{ generic, ... }:

let pkg =
  { lib, coriolis-crlcore, coriolis-hurricane
  , python3Packages, coriolis-cumulus }:
  {
    name = "coriolis-stratus1";
    src = ../stratus1;

    propagatedBuildInputs = [
      coriolis-crlcore coriolis-hurricane coriolis-cumulus
    ];
    postInstall = ''
      ln -s -t $out/${python3Packages.python.sitePackages} \
        $out/${python3Packages.python.sitePackages}/stratus/*
    '';
    pythonImportsCheck = [ "stratus" "patterns" "patread" "synopsys" "utils" "util" ];

    meta.license = lib.licenses.gpl2;
  };
in generic pkg
