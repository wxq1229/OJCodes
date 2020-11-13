#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef double db;

const int DAYS[] = {0, 31, -1, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

const int N = 1e5 + 10;

bool chk1(int y) { return y < 0 ? (y+1) % 4 == 0 : y % 4 == 0; }
bool chk2(int y) { return (y % 4 == 0 && y % 100 != 0) || y % 400 == 0; }

pair<int,int> calc1(int d) {
	return make_pair((d-1) / (365*3 + 366), (d-1) % (365*3 + 366) + 1);
}
int C400;
pair<int,int> calc2(int d) {
	return make_pair((d - 1) / C400, (d-1)%C400 + 1);
}

int r[N];

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int bdays = 0;
	for (int i = -4713; i <= -1; ++i)
		bdays += chk1(i) ? 366 : 365;
	for (int i = 0; i < 400; ++i)
		if (chk2(i)) C400 += 366;
		else C400 += 365;
	int days = 0;
	for (int y = -4713; y <= 1581; ++y) {
		if (y == 0) continue;
		if (chk1(y)) { days += 366; }
		else days += 365;
	}
	for (int mon = 1; mon < 10; ++mon)
		days += mon==2 ? 28 : DAYS[mon];
	days += 4;
	const int rem = DAYS[10] - 14 + DAYS[11] + DAYS[12];
//	cerr << days << '\n';
	int n;
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> r[i];
	}
	for (int i = 1; i <= n; ++i) {
		int year = 0, month = 1, day = 0;
//		++r[i];
		if (r[i] + 1 <= days) {
			if (r[i] + 1 <= bdays) {
				pair<int,int> p = calc1(r[i] + 1);
				year = p.first * 4 - 4713;
	//			cerr << "Second: " << p.second << '\n';
	//			cerr << "Y: " << year << '\n';
				int tmp = p.second;
				for (;;) {
	//						cerr << y << '\n';
					int DAY = chk1(year) ? 366 : 365;
					if (DAY >= tmp) break;
					tmp -= DAY;
					++year;
				}
				month = 1;
				for (int j = 1; j <= 12; ++j) {
					if (j == 2) {
						int DAY = 0;
						if (chk1(year)) DAY = 29;
						else DAY = 28;
						if (tmp <= DAY) break;
						tmp -= DAY;
						++month;
					} else {
						if (tmp <= DAYS[j]) break;
						tmp -= DAYS[j];
						++month;
					}
				}
				day = tmp;				
			} else {
//				cerr << "F\n";
				int delta = r[i]+1 - bdays;
				// 1.1.0 + delta
				pair<int,int> p = calc1(delta);
				year = p.first * 4 + 1;
				int tmp = p.second;
				for (;;) {
	//						cerr << y << '\n';
					int DAY = chk1(year) ? 366 : 365;
					if (DAY >= tmp) break;
					tmp -= DAY;
					++year;
				}
				month = 1;
				for (int j = 1; j <= 12; ++j) {
					if (j == 2) {
						int DAY = 0;
						if (chk1(year)) DAY = 29;
						else DAY = 28;
						if (tmp <= DAY) break;
						tmp -= DAY;
						++month;
					} else {
						if (tmp <= DAYS[j]) break;
						tmp -= DAYS[j];
						++month;
					}
				}
				day = tmp;				
			}
		} else {
			// 1582.10.14 + delta
			int delta = r[i] - days + 1;
			if (delta <= rem) {
				year = 1582;
				if (delta <= DAYS[10] - 14) {
					month = 10;
					day = delta + 14;
				} else {
					// 1582.11.0 + delta
					delta -= (DAYS[10] - 14);
					month = 11;
					for (int j = 11; j <= 12; ++j) {
						if (DAYS[j] >= delta) break;
						delta -= DAYS[j];
						++month;
					}
					day = delta;
				}
			} else {
				// 1583.1.0 + delta
				delta -= rem;
				if (delta <= 365) {
					year = 1583;
					month = 1;
					for (int j = 1; j <= 12; ++j) {
						int DAY = j == 2 ? 28 : DAYS[j];
						if (DAY >= delta) break;
						++month;
						delta -= DAY;
					}
					day = delta;
				} else {
					delta -= 365;
					// 1584.1.0 + delta
					pair<int,int> p = calc2(delta);
					year = 400 * p.first + 1584;
					int tmp = p.second;
//					cerr << year << " " << tmp << '\n';
					for (;;) {
//						cerr << y << '\n';
						int DAY = chk2(year) ? 366 : 365;
						if (DAY >= tmp) break;
						tmp -= DAY;
						++year;
					}
//					cerr << year << " " << tmp << '\n';
					month = 1;
					for (int j = 1; j <= 12; ++j) {
						int DAY = 0;
						if (j == 2) DAY = chk2(year) ? 29 : 28;
						else DAY = DAYS[j];
						if (DAY >= tmp) break;
						tmp -= DAY;
						++month; 
					}
					day = tmp;
				}
			}
		}
		cout << day << " " << month << " " << abs(year);
		if (year < 0) cout << " BC\n";
		else cout << '\n';
	}
	return 0;
}