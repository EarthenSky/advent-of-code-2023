
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

let string_of_char ch = String.make 1 ch

let remove_adj_duplicates list = 
    List.fold_right (fun x a -> if List.hd a = x then a else x :: a) list [0]

let file = "day3/input"
let () = 
    let lines = read_lines file in
    let h = List.length lines in
    let w = String.length (List.hd lines) in
    let matrix = Array.make (w * h) 0 in
    let sum_list = ref [] in
    
    for y = 0 to h-1 do
        let line = (List.nth lines y) ^ "." in
        let a = ref [] in
        for x = 0 to w do
            let ch = line.[x] in
            if is_digit ch then
                a := (ch :: (!a))
            else if not (is_digit ch) && (List.length (!a)) > 0 then 
                let len = List.length (!a) in
                let num_str = List.fold_left (fun a ch -> (string_of_char ch) ^ a) "" (!a) in
                let num = int_of_string num_str in
                for i = 1 to len do
                    matrix.(y * w + x - i) <- num
                done;
                a := []
        done
    done;

    for y = 0 to h-1 do
        let line = List.nth lines y in
        for x = 0 to w-1 do
            let ch = line.[x] in
            if not (is_digit ch) && ch == '*' then begin
                let tmp_list1 = [
                    matrix.((y-1) * w + x - 1);
                    matrix.((y-1) * w + x);
                    matrix.((y-1) * w + x + 1)
                ] in
                let tmp_list2 = [
                    matrix.((y+1) * w + x - 1);
                    matrix.((y+1) * w + x);
                    matrix.((y+1) * w + x + 1)
                ] in
                let tmp_list3 = [
                    matrix.(y * w + x - 1);
                    matrix.(y * w + x + 1)
                ] in
                let no_zero_list = List.filter (fun x -> x <> 0) (tmp_list3 @ (remove_adj_duplicates tmp_list2) @ (remove_adj_duplicates tmp_list1)) in
                if List.length no_zero_list == 2 then
                    sum_list := (List.fold_left ( * ) 1 no_zero_list) :: !sum_list;
                    List.iter (Printf.printf "%d ") !sum_list; Printf.printf "\n"
            end
        done
    done;

    Printf.printf "= %d \n" (List.fold_left (+) 0 !sum_list)