# advent-of-code-2023
 my solutions to advent of code 2023

# languages:
- ocaml
- idris
- handwritten assembly
- LLVM
- other IR languages?

## ocaml

### install
sudo apt install opam
opam init -y
eval $(opam env)

### optional
opam install dune ocaml-lsp-server odoc ocamlformat utop

### usage
- iterpreter: ocaml file.ml
- compiled: ocamlbuild file.native
