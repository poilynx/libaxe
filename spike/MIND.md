# 一些想法 #
## Object hierarchy ##

* box
  * seq
    * list
    * vector
    * deq
    * string
  * map
    * hashmap
    * avltree
* iter
* tuple
  * pair


## Operations ##
global-namespace: free

box: maxsize, size, begin, end, at, empty, clear, clone, merge, dump, shrink

seq: [m]push, pop, front, back, sort, reverse, pour

map: add, rmkey, rm, count, find

tuple: i8/u8 .. i64/u64, float, double, cstr, box, tuple(fmt, ...), length, get

pair: 

iter: prev, next, forward, back, remove, ref, equal

## Note ##

seq和map不是具体的结构体，只是对box的分类标记，在一些接口调用如ax\_seq\_push中，会断言该标记


## Simple ##
vector:
```c
ax_box_t* v = ax_vector_alloc("d");
ax_seq_assign(ax_tuple_alloc("d*", ax_2, 1, 2)); // 使用tuple构造vector
ax_seq_push(v, 3); 			//压入单值3
ax_seq_mpush(v, ax_2, 4, 5); 		//压入4, 5
int n;
ax_seq_back(v, &n); 			//get last element from sequence
ax_seq_pop(v);
ax_iter_t* it = ax_box_begin(v); 	//get first element iterator
while(ax_iter_over(t)) {
	printf("%d\n", *(int*)ax_iter_data());
	ax_iter_next(it);
}
ax_free(it);
ax_free(v);
```
avltree:
```c
ax_box_t* m = ax_avltree_alloc("ds");
ax_map_assign(ax_tuple_alloc("P[ds]*", ax_2, 1, "Beijing", 2, "Shanghai"));
ax_map_add(m, 3, "Tianjin");
ax_map_add(m, 4, "Chongqing");
ax_iter_t* it = ax_box_begin(m);
while(ax_iter_over(it)) {
	ax_pair_t pair = ax_iter_data(it);
	printf("%d -> %s\n", ax_pair_i32(pair, ax_0), ax_pair_i32(pair, ax_1));
	ax_iter_next(it);
}
AX_FOREACH(it, m) {
	printf("%d -> %s\n", ax_tuple_i32(pair, 0), ax_tuple_cstr(pair, 1));
	ax_iter_rm(it);
}
ax_free(it);
ax_free(m);

```
