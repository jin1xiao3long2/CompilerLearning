/*
 *  program ::= declaration  (declaration)* ;
 *
 *  declaration ::= type_specifier ID declaration' ;
 *
 *  declaration' ::= ';'
 *                        | '[' NUM ']' ';'
 *                        | '(' params ')' compound_stmt
 *                        ;
 *
 * type_specifier ::= INT
 *                            | VOID
 *                            ;
 *
 *  params ::= void_param_list
 *                 | int_param_list
 *                 ;
 *
 * void_param_list ::= VOID ( ID  ('[' ']')?  ( ',' param)* )? ;
 *
 *  int_param_list ::= INT ID ( '[' ']' )? ( ',' param )* ;
 *
 * param ::= type_specifier ID ( '[' ']' )? ;
 *
 * compound_stmt ::= '{' (var_declaration)* (statement)* '}' ;
 *
 * statement ::= expression_stmt
 *                     | compound_stmt
 *                     | selection_stmt
 *                     | iteration_stmt
 *                     | return_stmt
 *                     ;
 *
 * expression_stmt ::= expression ';'
 *                                | ';'
 *                                ;
 *
 *  selection_stmt ::= IF '(' expression ')' statement ( ELSE statement)? ;
 *
 *  iteration_stmt ::= WHILE '(' expression ')' statement ;
 *
 *  return_stmt ::= RETURN (expression)?
 *
 *  expression ::= var '=' expression
 *                       | simple_expression
 *                       ;
 *
 * var ::= ID ( '[' expression ']' )? ;
 *
 * simple_expression ::= additive_expression (relop additive_expression)? ;
 *
 * relop ::= '<=' | '<' | '>' | '>=' | '==' | '~=' ;
 *
 * additive_expression ::= term (addop term)* ;
 *
 * addop ::= '+' | '-' ;
 *
 * term ::= factor (mulop factor)*
 *
 * mulop ::= '*' | '/' ;
 *
 * factor ::= '(' expression ')'
 *               | ID factor'
 *               | NUM
 *               ;
 *
 * factor' ::= '[' expression ']'
 *                | '(' args ')'
 *                | NULL
 *                ;
 *
 * args ::= expression ( ',' expression)*
 *            | NULL
 *            ;
 */