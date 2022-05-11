double pie_area(double x1, double x2, double y, double r) {
    double th1 = atan2(y, x1), th2 = atan2(y, x2), thd = th2 - th1;
    if(thd < -M_PI) thd += 2 * M_PI;
    else if(thd > M_PI) thd -= 2 * M_PI;
    return r * r * thd / 2.0;
}
double poly_circle_intersection(point o, double r, polygon &poly) {
    double sm = 0.0; // Stokes' theorem
    for(int i = 0; i < poly.size(); ++i) {
        point p = poly[i], q = poly[(i + 1) % poly.size()];
        point xunit = setnorm(q - p);
        double xi = dot(p - o, xunit), xf = xi + abs(q - p);
        double y = cross(xunit, p - o);
        if(abs(y) < r) {
            double xint = sqrt(r * r - y * y);
            if(xi < -xint) sm += pie_area(xi, min(-xint, xf), y, r);
            if(xint < xf) sm += pie_area(max(xint, xi), xf, y, r);
            double ml = max(-xint, xi), mr = min(xint, xf);
            double mlen = max(mr - ml, 0.0);
            sm -= mlen * y / 2.0;
        } else {
            sm += pie_area(xi, xf, y, r);
        }
    }
    return sm;
}
