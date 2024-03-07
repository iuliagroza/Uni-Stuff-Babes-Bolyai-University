% Recursive model: 
% count_elem(l1l2...ln, e) = {
%                                       0, if l1l2...ln = 0
%                                       count_elem(l2...ln, e), if l1 != e
%                                       1 + count_elem(l2...ln, e, C+1), otherwise
%                                   }
%
% Flow model: 
% count_elem(i, i, o)
% count_elem(L - initial list, e - real number)

count_elem([], _, 0).
count_elem([H|T], E, N) :-
	E = H, !,
    count_elem(T, E, N1),
    N is N1 + 1.
count_elem([_|T], E, N) :-
	count_elem(T, E, N).

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
%                       {l1} U set(remove_elem(l2...ln, l1)), otherwise
%                  }
%
% Flow model: 
% set(i, o)
% set(L - initial list, R - resulting list)

set([], []).
set([H|T], [[H,C]|TR]) :-
    count_elem([H|T], H, C),
	remove_elem(T, H, Y),
	set(Y, TR).

% Recursive model:
% create_sol(l1l2...ln) = {
%                               0, if l1l2...ln = 0
%                               create_sol(l2l3...ln), if  
% }

create_sol([], []).
create_sol([H|T], [E,C|R]) :-
    count_elem([H|T], E, C),
    create_sol([T], R).

