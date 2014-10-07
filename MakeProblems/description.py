[Time-limit]
1000 ms
[/Time-limit]

[Memory-limit]
65536 KB
[/Memory-limit]

[Description]
k倍多重正整数集合的定义是：在一个多重集合（元素可以重复）中，不存在一个正整数是另一个正整数的k倍。
给你n个正整数，你可以选择其中一些数构成k倍多重正整数集合。请求出最多能选出多少数来构成它。
[/Description]


[Input]
第一行有两个整数n, k(1 <= n <= 10^5, 1 <= k <= 10^9)。
接下来一行有n个正整数 a1, a2, ..., an (1 <= ai <= 10^9)。
[/Input]

[Output]
最多能选出多少数构成k倍多重正整数集合。
[/Output]
 
[Sample-input]
样例1：
6 2
2 3 6 5 4 10

样例2：
2 2
2 2
[/Sample-input]


[Sample-output]
样例1：
3

样例2：
2
[/Sample-output]

[Hint]
第一个样例中，我们选择2，3，5即可满足要求，因为k == 2，不存在一个数是另一个数的两倍。
第二个样例中，我们选择2，2即可满足要求，因为k == 2，2也不是2的两倍，注意多重集合元素可以重复。
[/Hint]

[Source]
implus
[/Source]

