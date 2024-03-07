% Recursive model: 
% remove_elem(l1l2...ln, e) = {
%                               0, if l1l2...ln = 0
%                               {l1} U remove_elem(l2...ln, e), if l1 != e
%                               remove_elem(l2...ln, e), otherwise
%                            }
%
% Flow model: 
% remove_elem(i, i, o)
% remove_elem(L - initial list, e - real number, R - resulting list)

remove_elem([], _, []).
remove_elem([H|T], E, Tr) :-
	E = H, !,
	remove_elem(T, E, Tr).
remove_elem([H|T], E, [H|Tr]) :-
	remove_elem(T, E, Tr).

% Recursive model: 
% set(l1l2...ln) = {
%                       0, if l1l2...ln = 0
%                       {l1} U set(removeElem(l2...ln, l1)), otherwise
%                  }
%
% Flow model: 
% set(i, o)
% set(L - initial list, R - resulting list)

set([], []).
set([H|T], [H|X]) :-
	remove_elem(T, H, Y),
	set(Y, X).

% Recursive model: 
% insert_elem(l1l2...ln, e) = {
%                               {e}, if l1l2...ln = 0
%                               {l1} U insert_elem(l2...ln, e), if l1 <= e
%                               {e, l1} U insert_elem(l2...ln, e), otherwise
%                            }
%
% Flow model: 
% insert_elem(i, i, o)
% insert_elem(L - sorted list, e - real number, R - resulting list)

insert_elem([], E, [E]).
insert_elem([H|T], E, [E|Tr]) :-
	E =< H, !,
	insert_elem(T, H, Tr).
insert_elem([H|T], E, [H|Tr]) :-
	insert_elem(T, E, Tr).

% Recursive model: 
% insertion_sort(l1l2...ln) = {
%                               0, if l1l2...ln = 0
%                               insertElem(insertion_sort(l2...ln), l1), otherwise
%                            }
%
% Flow model: 
% insertion_sort(i, o)
% insertion_sort(L - initial list, R - resulting list)

insertion_sort([], []).
insertion_sort([H|T], R) :-
	insertion_sort(T, Rt),
	insert_elem(Rt, H, R).

sort_without_duplicates([], []).
sort_without_duplicates(L, R) :-
	set(L, Ls),
	insertion_sort(Ls, R).

% Testing examples:
% 1. sort_without_duplicates([2, 1, 3, 2, 4, 5, 5, 1], R). - regular case => R = [1, 2, 3, 4, 5].
% 2. sort_without_duplicates([], R). - base case => R = [].
% 3. sort_without_duplicates([1, 2, 3, 4, 5], R). - case with already sorted list without duplicates => R = [1, 2, 3, 4, 5].
% 4. sort_without_duplicates([1, 1, 1, 1], R). - case with only duplicates => R = [1].
% 5. sort_without_duplicates([4, 3, 2, 10.5, -4], R). - case without duplicates > R = [-4, 2, 3, 4, 10.5].


% Recursive model: 
% sort_sublists(l1l2...ln) = {
%                               0, if l1l2...ln = 0
%                               {l1} U sort_sublists(l2l3...ln), if l1 != list
%                                sort_without_duplicates(l1) U sort_sublists(l2l3...ln), otherwise
%                            }
%
% Flow model: 
% sort_sublists(i, o)
% sort_sublists(L - initial list, R - resulting list)

sort_sublists([], []).
sort_sublists([H|T], [Hr|Tr]) :-
	is_list(H),
	sort_without_duplicates(H, Hr),
	sort_sublists(T, Tr).
sort_sublists([H|T], [H|Tr]) :-
	sort_sublists(T, Tr).

% Testing examples:
% 1. sort_sublists([1, 2, [1, 3, -4, 3], 5, 1], R). - regular case => R = [1, 2, [-4, 1, 3], 5, 1].
% 2. sort_sublists([], R). - base case => R = [].
% 3. sort_sublists([1, 3, 187, 7], R). - case with no sublists => R = [1, 3, 187, 7].
% 4. sort_sublists([1, 2, [3, 5, 5, 4, 5, -6, 3, 4], 3, 7, [1, 2], [34, 34, 1]], R). - case with multiple sublists => R = [1, 2, [-6, 3, 4, 5], 3, 7, [1, 2], [1, 34]].
% 5. sort_sublists([[1]], R). - case with one sublist => R = [[1]].