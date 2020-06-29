{ stdenv, lib, pkgconfig, autoreconfHook, gnome3 }:

stdenv.mkDerivation {
  name = "cliff";
  src = lib.cleanSource ./.;
  buildInputs = [ pkgconfig autoreconfHook gnome3.gtkmm ];
  doCheck = true;
}
