```c
                             1 
stack<int> sta;
sta.push(7);

for (int i = 1; i < 5; i++) {
	sta.push(i);
}

cout << sta.size() << endl;
cout << sta.top() << endl;

sta.pop();

while (!sta.empty()) {
	cout << sta.top() << endl;
	sta.pop();
}

                              2
queue<int> que;
que.push(7);

for (int i = 1; i < 5; i++) {
	que.push(i);
}

cout << que.size() << endl;
cout << que.front() << endl;

que.pop();

while (!que.empty()) {
	cout << que.front() << endl;
	que.pop();
}

                              自定义类型
struct node {
	int x, y;
};

    queue<node> que;
    node a;
    a.x = 1;
    a.y = 2;
    que.push(a);
    node t = que.front();
    cout << t.x << " " << t.y << endl;
    que.push((node){3, 4});        // 初始化
```





