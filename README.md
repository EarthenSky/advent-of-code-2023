# advent-of-code-2023
My solutions to advent of code 2023. This year's theme: "polar extremes"

# languages
- [x] ocaml - 1, 2, 3
- [/] idris2 - 4
- [ ] QBE
- [ ] LLVM
- [ ] other IR languages?
- [ ] F#
- [ ] other funky programming languages?

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

### my take
- less slick version of haskell, but with the promise that you can fall back to mutable code if needed for performance reasons
- 
- 6/10

## idris2

### install
- NOTE: install homebrew
- brew install idris2

### usage
idris2 part1.idr -o part1
./build/exec/part1

### my take
- haskell but with no documentation and requiring detail to the irrelevant (or something along those lines)
- an accidental low-level language
- 1/10

## QBE

### install
