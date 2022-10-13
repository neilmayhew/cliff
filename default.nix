{ stdenv, lib, pkg-config, autoreconfHook, gtkmm3 }:

stdenv.mkDerivation {
  name = "cliff";
  src = lib.cleanSource ./.;
  buildInputs = [ pkg-config autoreconfHook gtkmm3 ];
  doCheck = true;
}
