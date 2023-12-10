# advent-of-code-2023
My solutions to advent of code 2023. This year's theme: "polar extremes"

# languages
- [x] ocaml - 1, 2, 3
- [x] idris2 - 4
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
- the merge between functional & imperative style is not clean; I felt that I was discouraged from doing any mutable code, and when I did do it, it wasn't as good. Mutable code is not first class.
- 6/10

## idris2

### install
- NOTE: install homebrew
- brew install idris2

### usage
idris2 part1.idr -o part1
./build/exec/part1

### my take
- haskell but with no documentation and requiring detail for the irrelevant (or something along those lines)
- an accidental low-level language
- (but if I read the book in more detail, it might have been better...)
- I also could not understand the documentation at ALL, which is fair since the language is still under development
- 2/10

## QBE

### install
