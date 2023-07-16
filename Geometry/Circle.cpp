
struct circle {
    Pd c; 
    db r;
    circle():c(0.0,0.0), r(0) {}
    circle (Pd _c, db _r) : c(_c), r(_r) {}
};

const db PI = acos(-1.0);

std::vector<Pd> circle_circle_intersection(const circle a,const circle b) {
    db d = abs(a.c - b.c);
    if(sgn(d - a.r - b.r) > 0 || sgn(d - std::abs(a.r - b.r)) < 0) return {};
    db l = (abs2(a.c - b.c) + a.r * a.r - b.r * b.r) / 2.0 / d;
    db h = std::sqrt(std::max(db(0), a.r * a.r - l * l));
    Pd vl = (b.c - a.c);
    Pd vh = vl.rotate90().trunc(h);
    vl = vl.trunc(l);
    Pd p1 = a.c + vl + vh;
    Pd p2 = a.c + vl - vh;
    return {p1, p2};
}