{ nixpkgs ? import <nixpkgs> {} }:

with nixpkgs;
with pkgs;

stdenv.mkDerivation {
  name = "cliff";
  src = ./.;
  buildInputs = [ pkgconfig autoreconfHook gnome3.gtkmm ];
  doCheck = true;
}
