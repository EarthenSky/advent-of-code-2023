import System.IO  
import Control.Monad
import Data.List
import Data.Maybe
import Debug.Trace

apply_map :: [Int] -> [(Int, Int, Int)] -> [Int]
apply_map seeds mapping = foldl (\acc seed -> 
    let result = foldl (\acc (dest, src, a) ->
            if (seed >= src) && (seed < (src + a))
            then seed - src + dest
            else acc) seed mapping
    --in traceShow result (result:acc)
    in result:acc
    ) [] seeds

to_int_list :: String -> [Int]
to_int_list str = map read (words str)

tuplify3 [x, y, z] = (x, y, z)

main = do
    -- read input from file & parse it
    file_handle <- openFile "input" ReadMode
    first_line <- hGetLine file_handle
    --print first_line
    let seeds = to_int_list (snd (splitAt ((fromMaybe 0 (findIndex (==':') first_line)) + 1) first_line))
    print seeds

    contents <- hGetContents file_handle
    let mapping_list = foldl (\acc line ->
            if line == "" then acc
            else if isJust (findIndex (==':') line) then []:acc
            else let head:tail = acc in
                ((tuplify3 (to_int_list line)):head):tail
            ) [] (lines contents)

    -- sort mappings too
    let sorted_mapping_list = reverse (map sort mapping_list)
    --print sorted_mapping_list
    print (foldl apply_map seeds sorted_mapping_list)
    print (minimum (foldl apply_map seeds sorted_mapping_list))
