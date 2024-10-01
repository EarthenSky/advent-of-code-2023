import System.IO  
import Control.Monad
import Data.List
import Data.Maybe
import Debug.Trace

type Range = (Int, Int)

apply_range_map :: [Range] -> [(Int, Int, Int)] -> [Range]
apply_range_map seed_range_list mapping = 
    foldl (\acc (range_start, range_len) ->
        let
            (result_start, result_len, result_list) =
                foldl (\(running_start, running_len, acc2) (dest, src, a) ->
                    let
                        running_end = running_start + running_len
                        src_end = src + a
                    in
                    if running_len == 0 then (-1, 0, acc2)
                    -- if the two ranges ever overlap
                    else if src < running_end && src_end >= running_start then
                        -- if range is fully covered by src_range
                        if src <= running_start && (running_end-1) < src_end then
                            (-1, 0, (running_start + (dest - src), running_len):acc2)
                        -- if range ends in src_range
                        else if running_start <= src && (running_end-1) < src_end then
                            (-1, 0, [(running_start, src - running_start), (dest, running_end - src)] ++ acc2)
                        -- if range fully overwrites the current
                        else if running_start >= src && (running_end-1) >= src_end then
                            (src_end, running_len - ((src_end - 1) - running_start), (running_start + (dest - src), (src_end - 1) - running_start):acc2)
                        -- range must start before & end past
                        else
                            (src_end, running_len - ((src_end - 1) - running_start), [(running_start, src - running_start), (dest, a)] ++ acc2)
                    else (running_start, running_len, acc2)
                ) (range_start, range_len, []) mapping
            final_result = 
                if result_len == 0 then result_list
                else (result_start, result_len):result_list
        in (final_result ++ acc)
    ) [] seed_range_list

to_int_list :: String -> [Int]
to_int_list str = map read (words str)

tuplify3 [x, y, z] = (x, y, z)
tuplify2 [x, y] = (x, y)

chunksOf2 :: [a] -> [(a, a)]
chunksOf2 [] = []
chunksOf2 xs =
    let (ys, zs) = splitAt 2 xs
    in  (tuplify2 ys) : chunksOf2 zs

main = do
    -- read input from file & parse it
    file_handle <- openFile "input" ReadMode
    first_line <- hGetLine file_handle
    let seeds = to_int_list (snd (splitAt ((fromMaybe 0 (findIndex (==':') first_line)) + 1) first_line))
    let seed_pairs = chunksOf2 seeds

    contents <- hGetContents file_handle
    let mapping_list = foldl (\acc line ->
            if line == "" then acc
            else if isJust (findIndex (==':') line) then []:acc
            else let head:tail = acc
                 in  ((tuplify3 (to_int_list line)):head):tail
            ) [] (lines contents)

    -- sort mappings too
    let sorted_mapping_list = reverse (map (sortBy (\(a, b, c) (d, e, f) -> compare b e)) mapping_list)
    print $ minimum (map fst (foldl apply_range_map seed_pairs sorted_mapping_list))
