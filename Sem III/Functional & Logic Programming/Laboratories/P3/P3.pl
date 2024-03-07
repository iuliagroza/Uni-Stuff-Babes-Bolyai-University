% Recursive model:
% create_list(n) = {
% 	                0, if l1l2...ln = 0
% 	                {n} U create_list(n - 1), otherwise
%                  }
%
% Flow model:
% create_list(i, o)
% create_list(n - real number, R - resulting list)

create_list(0, []).
create_list(N, [N|R]) :-
    N > 0,
    N1 is N - 1,
    create_list(N1, R).

% Recursive model:
% insert(l1...ln, e) = {
% 	                        {e}, if l1l2...ln = 0
%                           {e} U l1l2...ln, otherwise
% 	                        {l1} U insert(l2l3...ln, e), otherwise
%                      }
%
% Flow model:
% insert(i, i, o)
% insert(L - initial list, e - real number, R - resulting list)

insert([], E, [E]).
insert([H|T], E, [E,H|T]).
insert([H|T], E, [H|R]) :- 
         insert(T, E, R).

% Recursive model:
% permute(l1...ln) = {
% 	                        0, if l1l2...ln = 0
% 	                        insert(permute(l2l3...ln), l1), otherwise
%                    }
%
% Flow model:
% permute(i, o)
% permute(L - initial list, R - resulting list)

permute([], []).
permute([H|T], R) :-
    permute(T, RP),
    insert(RP, H, R).

abs_diff(A, B, R) :-
    A > B, !,
    R is A - B.
abs_diff(A, B, R) :-
    R is B - A.

% Recursive model:
% check(l1...ln, e) = {
% 	                    true, if l1l2...ln = 0
% 	                    true, if abs_diff(l1, e) = 1
% 	                    check(l2...ln, e), if n > 1
% 	                    false, otherwise
%                     }
% 
% Flow model:
% check(i, i)
% check(L - initial list, e - real number)

check([], _).
check([H|_], E) :-
    abs_diff(E, H, R),
    R =:= 1, !.
check([_|T], E) :-
    check(T, E).

% Recursive model:
% check_perm(l1l2...ln, k1k2...km) = {
%                                       true, if l1l2...ln = 0
%                                       check_perm(l2l3...ln), if check(l2l3...ln, l1) = true
%                                       false, otherwise
%                                    }
%
% Flow model:
% check_perm(i)
% check_perm(L - intial list)
 	
check_perm([]) :- !.
check_perm([H|T]) :-
    check(T, H),
    check_perm(T).

one_solution(L, R) :-
    permute(L, R),
    check_perm(R).

all_solutions(N, R) :-
    create_list(N, RL),
    findall(RP, one_solution(RL, RP), R).

% Testing examples:
% 1. all_solutions(0, R). - base case => R = [[]].
% 2. all_solutions(1, R). => R = [[1]].
% 3. all_solutions(3, R). - regular case => R = [[3, 2, 1], [2, 3, 1], [2, 1, 3], [3, 1, 2], [1, 3, 2], [1, 2, 3]].
% 4. all_solutions(4, R). - bigger input case => [[4, 3, 2, 1], [3, 4, 2, 1], [3, 2, 4, 1], [3, 2, 1, 4], [4, 2, 3, 1], [2, 4, 3|...], [2, 3|...], [2|...], [...|...]|...].