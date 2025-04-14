{
  description = "Vo1dix Flake";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-24.11";
  };

  outputs = 
    {
      nixpkgs,
      ...
    }:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
    in
    {
      devShells.${system} = {
        default = pkgs.mkShell {
          buildInputs = with pkgs; [
            clang
            gcc
            gnumake
            nasm
            binutils
            pkgsCross.i686-embedded.buildPackages.gcc
            grub2
            xorriso
            qemu
          ];
        };
      };
    };
}
