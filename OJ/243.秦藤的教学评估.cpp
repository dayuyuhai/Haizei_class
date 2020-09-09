/*************************************************************************
	> File Name: 243.秦藤的教学评估.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Sun 24 May 2020 03:41:45 PM CST
 ************************************************************************/

#include<iostream>
#include<string.h>
using namespace std;

typedef long long ll;

ll arr[200005];
ll sum[200005];

ll binary_search(ll *a, ll t) {
	ll head = 0, tail = t + 1, mid;
	while (head < tail) {
		mid = (head + tail) >> 1;
		if (a[mid] & 1) tail = mid;
		else head = mid + 1;
	}
	return (tail == t + 1) ? -1 : tail;
}

ll judge(ll n) {
	memset(arr, 0, sizeof(arr));
	memset(sum, 0, sizeof(sum));
	ll s, d, e, max = 0;
	for (ll i = 0; i < n; i++) {
		cin >> s >> e >> d;
		max = max > e ? max : e;
		for (ll j = s; j <= e; j += d) {
			arr[j] += 1;
		}
	}
	for (ll i = 0; i <= max; i++) {
		for (ll j = 0; j <= i; j++) {
			sum[i] += arr[j];
		}
	}
	return max;
}

int main() {
	ll T, n, ret;
	cin >> T;
	while (T--) {
		cin >> n;
		ll t = judge(n);
		ret = binary_search(sum, t);
		if (ret == -1) printf("Poor QIN Teng:(\n");
		else printf("%lld %lld\n", ret, sum[ret] - sum[ret - 1]);
	}
	return 0;
}
