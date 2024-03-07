% Recursive model: 
% replace(l1l2...ln, e, newE) = {
%                                   0, if l1l2...ln = 0
%                                   {l1} U replace(l2...ln, e, newE), if l1 != e
%                                   {newE} U replace(l2...ln, e, newE), otherwise
%                               }
%
% Flow model: 
% replace(i, i, i, o)
% replace(L - initial list, e - real number, newE - real number, R - resulting list)

replace([], _, _, []).
replace([H|T], E, NewE, [NewE|TR]):-
    H =:= E, !,
    replace(T, E, NewE, TR).
replace([H|T], E, NewE, [H|TR]):-
    replace(T, E, NewE, TR).

% Testing examples:
% 1. replace([], 11, 12, R). - base case => R = [].
% 2. replace([1, 79, 5, -3, 5, 5, 79, 0, 1], 5, 0, R). - regular case => R = [1, 79, 0, -3, 0, 0, 79, 0, 1].
% 3. replace([1, 2, 3, 4, 5], 10, 1, R). - case with no replacement performed => R = [1, 2, 3, 4, 5].
% 4. replace([1], 1, 1, R). - case with one-element initial list that is replaced and e = newE => R = [1].
% 5. replace([0.5, 12.5, -13.79, 0.5, 100, 0.5, 0.5, 0.5], 0.5, -100, R). - case containing real numbers => R = [-100, 12.5, -13.79, -100, 100, -100, -100, -100].


% Recursive model:
% sublist_rec(l1l2...lk, m, n, pos) = {
%                                       0, if m > n OR m < 1 OR n < 1
%                                       {l1}, if pos = n
%                                       {l1} U sublist_rec(l2...lk, m, n, pos + 1), if m <= pos < n 
%                                       sublist_rec(l2...lk, m, n, pos + 1), otherwise
%                                    }
%
% Flow model:
% sublist_rec(i, i, i, i, o)
% sublist_rec(L - initial list, m - integer, n - integer, pos - integer, R - resulting list)

sublist_rec(_, M, N, _, []):- M > N, !, false.
sublist_rec(_, M, _, _, []) :- M < 1, !, false.
sublist_rec([H|_], _, N, N, [H]):- !.
sublist_rec([H|T], M, N, Pos, [H|R]):- 
    M =< Pos, Pos < N, !,
    NewPos is Pos+1,
    sublist_rec(T, M, N, NewPos, R).
sublist_rec([_|T], M, N, Pos, R):- 
    NewPos is Pos+1,
    sublist_rec(T, M, N, NewPos, R).

sublist(L, M, N, R):-
    sublist_rec(L, M, N, 1, R).

% Testing examples:
% 1. sublist([1, 2, 3, 4, 5], 5, 3, R). - case with m > n => false.
% 2. sublist([1, 2, 3, 4, 5], -1, 5, R). - case with m < 1 => false.
% 3. sublist([1, 2, 3, 4, 5], 0, 0, R). - case with n < 1 => false.
% 4. sublist([1, 2, 3, 4, 5], 3, 7, R). - case with n > k => false.
% 5. sublist([1, 2, 3, 4, 5], 10, 11, R). - case with m > k => false.
% 6. sublist([1], 1, 1, R). - base case => R = [1].
% 7. sublist([1, 2, 3, 4, 5, 6, 7, 8, 9], 3, 9, R). - regular case => R = [3, 4, 5, 6, 7, 8, 9].