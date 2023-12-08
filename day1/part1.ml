(*

(* util *)

let print_list list =
  List.iter (Printf.printf "%d ") list;
  Printf.printf "\n"

let inc = fun x -> x + 1

let any_mod list i =
  List.exists (fun m -> i mod m = 0) list

(* const *)

let limit = 1000

(* behaviour *)

let () = 
  let nums = List.init (limit - 1) inc in
  let multiples_of_3_5 = List.filter (any_mod [3; 5]) nums in 
  let result = List.fold_left ( + ) 0 multiples_of_3_5 in
  print_int result;
  print_endline ""

*)

(* TODO: readfile [this] *)

(* docs: https://ocaml.org/docs/file-manipulation *)
let file = "input1"
let () = 
  let ic = open_in file in
  try
    let line = input_line ic in
    (* read line, discard \n *)
    print_endline line;
    (* write the result to stdout *)
    flush stdout;
    (* write on the underlying device now *)
    close_in ic
    (* close the input channel *)
  with e ->
    (* some unexpected exception occurs *)
    close_in_noerr ic;
    (* emergency closing *)
    raise e
