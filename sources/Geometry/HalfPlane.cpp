bool onLeft(Pd p, Ld l) {
	return cross(l.v, p - l.a) > 0;
}

template<typename Point>
std::vector<Point> hp(std::vector<Line<Point>>& lines) {
	std::sort(lines.begin(), lines.end(), [&](auto l1, auto l2) {
		auto d1 = l1.v;
		auto d2 = l2.v;
		if (d1.up() != d2.up()) {
			return d1.up() == 1;
		}
		return cross(d1, d2) > 0;
	});

	std::deque<Ld> ls;
	std::deque<Pd> ps;
	for (auto l: lines) {
		if (ls.empty()) {
			ls.push_back(l);
			continue;
		}

		while (!ps.empty() && !onLeft(ps.back(), l)) {
			ps.pop_back();
			ls.pop_back();
		}

		while (!ps.empty() && !onLeft(ps[0], l)) {
			ps.pop_front();
			ls.pop_front();
		}

		if (cross(l.v, ls.back().v) == 0) {
			if (dot(l.v, ls.back().v) > 0) {
				if (!onLeft(ls.back().a, l)) {
					assert(ls.size() == 1);
					ls[0] = l;
				}
				continue;
			}
			return {};
		}

		ps.push_back(intersection(ls.back(), l));
		ls.push_back(l);
	}

	while (!ps.empty() && !onLeft(ps.back(), ls[0])) {
		ps.pop_back();
		ls.pop_back();
	}
	if (ls.size() <= 2) {
		return {};
	}
	ps.push_back(intersection(ls[0], ls.back()));

	return {ps.begin(), ps.end()};
}