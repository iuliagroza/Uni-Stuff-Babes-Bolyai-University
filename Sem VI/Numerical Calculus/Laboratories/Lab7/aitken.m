function p = aitken(xi, fi, xx)
    n = length(xi);
    m = length(xx);
    p = zeros(m, 1);

    for j = 1:m
        Px = fi; 
        for k = 1:n-1
            for i = 1:n-k
                Px(i) = ((xx(j) - xi(i+k)) * Px(i) + (xi(i) - xx(j)) * Px(i+1)) / (xi(i) - xi(i+k));
            end
        end
        p(j) = Px(1);
    end
end
