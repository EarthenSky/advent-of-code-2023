open Printf

(* from: https://stackoverflow.com/questions/5774934/how-do-i-read-in-lines-from-a-text-file-in-ocaml *)
let read_lines file =
    let chan = open_in file in
    let lines = ref [] in

    try
        while true; do
        lines := input_line chan :: !lines
        done; !lines
    with End_of_file ->
        close_in chan;
        List.rev !lines

let is_alpha ch = match ch with 'a' .. 'z' | 'A' .. 'Z' -> true | _ -> false
let is_digit ch = match ch with '0' .. '9' -> true | _ -> false
let string_as_list str = List.rev (List.init (String.length str) (String.get str))
let parse_char ch = (int_of_char ch) - (int_of_char '0')
let char_as_string ch = String.make 1 ch
let first_and_last_chars_as_int list = int_of_string (char_as_string (List.hd list) ^ (char_as_string (List.nth list (List.length list - 1))))

let file = "day1/input"
let () = 
    let lines = read_lines file in
    let concat s c = c :: s in
    let remove_chars line = List.fold_left concat [] (List.filter is_digit (string_as_list line)) in
    let noletters = List.map remove_chars lines in
    let duplicate_singles = List.map (fun list -> if (List.length list) == 1 then (List.hd list) :: list else list) noletters in
    let sum = List.fold_left (fun a list -> a + (first_and_last_chars_as_int list)) 0 duplicate_singles in
    print_int sum;
    print_newline ()
