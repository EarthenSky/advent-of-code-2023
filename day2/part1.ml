
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

let rec filter_string f str = 
    let list = List.init (String.length str) (String.get str) in
    let filtered = List.filter f list in
    List.fold_left (fun a ch -> a ^ (String.make 1 ch)) "" filtered

let int_of_string_strong str = int_of_string (filter_string is_digit str)

let rec smaller_than pull1 pull2 =
    match pull1 with
    | [] -> false
    | x1 :: xs1 -> 
        match pull2 with
        | [] -> false
        | x2 :: xs2 -> 
            (x1 < x2) || (smaller_than xs1 xs2)

let reference_pull = [12; 13; 14]
let file = "day2/input"
let () = 
    let lines = read_lines file in
    let is_valid line = 
        match String.split_on_char ':' line with
        | x :: xs ->
            let id = int_of_string_strong x in
            let create_rgb_tuple str = 
                let list = String.split_on_char ',' str in
                let r = List.find_opt (fun str -> String.contains str 'd') list in
                let g = List.find_opt (fun str -> String.contains str 'n') list in
                let b = List.find_opt (fun str -> String.contains str 'l') list in
                [(match r with | Some r -> int_of_string_strong r | None -> 0);
                 (match g with | Some g -> int_of_string_strong g | None -> 0);
                 (match b with | Some b -> int_of_string_strong b | None -> 0)]
            in
            let bag_pulls = List.map create_rgb_tuple (String.split_on_char ';' (List.hd xs)) in
            List.exists (fun pull -> smaller_than reference_pull pull) bag_pulls, id
        | [] -> raise (Arg.Bad "line has no : char") 
    in
    let sum = List.fold_left (fun a (p, i) -> Printf.printf "%b %d \n" p i; if not p then a + i else a) 0 (List.map is_valid lines) in
    Printf.printf "%d \n" sum