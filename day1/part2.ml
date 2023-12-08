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

let is_digit ch = match ch with '0' .. '9' -> true | _ -> false
let list_of_string str = List.init (String.length str) (String.get str)
let two_ints_as_int x1 x2 = int_of_string ((string_of_int x1) ^ (string_of_int x2))

let rec first_digit_in_line line depth = match line with
| x :: xs -> 
    if is_digit x then depth, (int_of_char x) - (int_of_char '0')
    else first_digit_in_line xs (depth + 1)
| [] -> 1000, 1000 (* this refers to "too big" *)

(* same elements up to min length *)
let rec heads_match l1 l2 = 
    match l1 with
    | [] -> true
    | x1 :: xs1 ->
        match l2 with
        | [] -> true
        | x2 :: xs2 ->
            if x1 == x2 then heads_match xs1 xs2 
            else false

(* finds the first match of pat or None *)
let rec first_match (pat : char list) (line : char list)  depth =
    if heads_match pat line then Some depth
    else match line with
    | [] -> None
    | x :: xs -> first_match pat xs (depth + 1)

let min_tuple_of list =
    let m = List.fold_left (fun a (i, d) -> match i with | Some i -> min a i | None -> a) 1000 list in
    let (i, d) = List.find (fun (i, d) -> match i with | Some i -> i == m | None -> false) list in
    match i with 
    | None -> raise (Arg.Bad "list contains no Some")
    | Some x -> x, d

let first_letter_digit_in_line line digit_words =
    let mappings = List.map (fun (word, digit) -> first_match word line 0, digit) digit_words in
    min_tuple_of mappings

let first_real_digit_in_line line digit_words =
    let (i1, d1) = first_letter_digit_in_line line digit_words in
    let (i2, d2) = first_digit_in_line line 0 in
    if i1 < i2 then d1 else d2

let digit_words = List.map (fun (s, digit) -> list_of_string s, digit) [
    ("zero",0);("one",1);("two",2);("three",3);("four",4);
    ("five",5);("six",6);("seven",7);("eight",8);("nine",9)
]
let digit_words_rev = List.map (fun (s, digit) -> List.rev (list_of_string s), digit) [
    ("zero",0);("one",1);("two",2);("three",3);("four",4);
    ("five",5);("six",6);("seven",7);("eight",8);("nine",9)
]
let file = "day1/input"
let () = 
    let line_strings = read_lines file in
    let lines = List.map list_of_string line_strings in
    let solve_line line = two_ints_as_int (first_real_digit_in_line line digit_words) (first_real_digit_in_line (List.rev line) digit_words_rev) in
    let number_list = List.map solve_line lines in
    let sum = List.fold_left (+) 0 number_list in
    print_int sum;
    print_newline ();