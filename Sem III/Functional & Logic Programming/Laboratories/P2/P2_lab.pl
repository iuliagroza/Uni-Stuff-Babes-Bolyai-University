% is_prime(N, D) = {
%                       True, if D > N/2
%                       False, if N%D = 0
%                       is_prime(N, D+1), otherwise
%                  }

is_prime(N, D) :-
    D > N/2, !.
is_prime(N, D) :-
    N mod D =\= 0, !,
    D1 is D + 1,
    is_prime(N, D1).

prime(N) :-
    N > 1,
    is_prime(N, 2).

% sum_prime(S, P) = {
%                       [P], if S = P and prime(P)
%                       P U sumPrime(S-P, P+1), if S > P and prime(P)
%                       sumPrime(S, P+1), if S > P and prime(P)
%                       sumPrime(S, P+1), otherwise
%                   }   

sum_prime(S, S, [S]) :-
    prime(S).
sum_prime(S, P, [P|R]) :-
    S > P,
    prime(P),
    S1 is S - P,
    P1 is P + 1,
    sum_prime(S1, P1, R).
sum_prime(S, P, R) :-
    S > P,
    prime(P),
    P1 is P + 1,
    sum_prime(S, P1, R).
sum_prime(S, P, R) :-
    S > P,
    not(prime(P)),
    P1 is P + 1,
    sum_prime(S, P1, R).

sum_p(S, R) :-
    sum_prime(S, 2, R).

