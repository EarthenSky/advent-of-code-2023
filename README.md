# advent-of-code-2023
My solutions to advent of code 2023. This year's theme: "polar extremes"

# languages
- [x] ocaml - 1, 2
- [ ] idris
- [ ] handwritten assembly
- [ ] LLVM
- [ ] other IR languages?
- [ ] F#
- [ ] other functional programming languages?

# instructions

Please run this on linux or wsl

## ocaml

### install
sudo apt install opam
opam init -y
eval $(opam env)

### optional
opam install dune ocaml-lsp-server odoc ocamlformat utop

### usage
eval $(opam env)
- iterpreter: ocaml day1/part1.ml
- compiled: ocamlbuild day1/part1.native
