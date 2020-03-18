{
type token =
  | T_and | T_end | T_list | T_ref | T_bool | T_exit | T_mod 
  | T_return | T_char | T_false | T_new | T_skip | T_decl | T_for
  | T_nil | T_tail | T_def | T_head | T_nilq | T_true | T_else | T_if
  | T_not | T_elsif | T_int | T_or | T_const | T_var | T_eq 
  | T_lparen | T_rparen | T_plus | T_minus | T_times | T_eof
}


let digit  = ['0'-'9']
let letter = ['a'-'z']
let white  = [' ' '\t' '\r' '\n']

let var =['a'-'z' 'A'-'Z']+['a'-'z' 'A'-'Z' '0'-'9' '_' '?']

rule lexer = parse
    "and"  { T_and }
  | "end"    { T_end }
  | "list"    { T_list }
  | "ref"     { T_ref }
  | "bool"  { T_bool }
  | "exit"    { T_exit }
  | "mod"     { T_mod }
  | "return"   { T_return }
  | "char"    { T_char }
  | "false"    { T_false }
  | "new"     { T_new }
  | "skip"  { T_skip }
  | "decl"    { T_decl }
  | "for"     { T_for }
  | "nil"   { T_nil }
  | "tail"    { T_tail }
  | "def"    { T_def }
  | "head"     { T_head }
  | "nil?"  { T_nilq }
  | "true"    { T_true }
  | "else"     { T_else }
  | "if"   { T_if }
  | "not"  { T_not }
  | "elsif"    { T_elsif }
  | "int"     { T_int }
  | "or"   { T_or }


  | digit+   { T_const }
  | var   { T_var }

  | '='      { T_eq }
  | '('      { T_lparen }
  | ')'      { T_rparen }
  | '+'      { T_plus }
  | '-'      { T_minus }
  | '*'      { T_times }

  | white+               { lexer lexbuf }
  (* thelei parapanw \ apo katw *)
  | "'" [^ '\n']* "\n"   { lexer lexbuf } 

  |  eof          { T_eof }
  |  _ as chr     { 
      Printf.eprintf "invalid character: '%c' (ascii: %d)"
      chr (Char.code chr);
      lexer lexbuf 
      }

{
  let string_of_token token =
    match token with
      | T_and     -> "T_and"
      | T_end     -> "T_end" 
      | T_list    -> "T_list"
      | T_ref     -> "T_ref"
      | T_bool    -> "T_bool"
      | T_exit    -> "T_exit"
      | T_mod     -> "T_mod"  
      | T_return  -> "T_return"
      | T_char    -> "T_char"
      | T_false   -> "T_false"
      | T_new     -> "T_new"
      | T_skip    -> "T_skip"
      | T_decl    -> "T_decl"  
      | T_for     -> "T_for"
      | T_nil     -> "T_nil"
      | T_tail    -> "T_tail"
      | T_def     -> "T_def"
      | T_head    -> "T_head"
      | T_nilq    -> "T_nilq"
      | T_true    -> "T_true"
      | T_else    -> "T_else"
      | T_if      -> "T_if"
      | T_not     -> "T_not"
      | T_elsif   -> "T_elsif"
      | T_int     -> "T_int"
      | T_or      -> "T_or"
      | T_const   -> "T_const" 
      | T_var     -> "T_var" 
      | T_eq      -> "T_eq" 
      | T_lparen  -> "T_lparen" 
      | T_rparen  -> "T_rparen" 
      | T_plus    -> "T_plus" 
      | T_minus   -> "T_minus" 
      | T_times   -> "T_times" 
      | T_eof     -> "T_eof" 


  let main = 
    let lexbuf = Lexing.from_channel stdin in 
    let rec loop () =
      let token = lexer lexbuf in 
      Printf.printf "token=%s, lexeme=\"%s\"\n"
        (string_of_token token) (Lexing.lexeme lexbuf);
      if token <> T_eof then loop () in
    loop ()
}