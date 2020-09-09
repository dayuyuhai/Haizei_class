#include<haizei/gtest.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<haizei/linklist.h>

int cnt = 0, cnt_success = 0;

struct Function func_head, *func_tail = &func_head;

/*
node head;
node *tail = &head;
*/

int RUN_ALL_TESTS() {
	for (struct LinkNode *p = func_head.p.next; p; p = p->next) {
		struct Function *func = Head(p, struct Function, p);
		printf(GREEN_HL("[====RUN====]") RED_HL(" %s") "\n", func->name);
		cnt = 0;
		cnt_success = 0;
		func->func();
		double rate = 1.0 * cnt_success / cnt * 100;
		if (cnt == cnt_success) {
			printf(GREEN("[") BLUE("%8.2lf%%  "), rate);
		} else {
			printf(GREEN("[") RED("%8.2lf%%  "), rate);
		}
		printf(GREEN("] ") "total : %d  success : %d\n", cnt, cnt_success);
	}

	/*
	node *p = head.next;
	for (; p; p = p->next) {
		printf(GREEN_HL("[====RUN====]") RED_HL(" %s") "\n", p->name);
		cnt = 0;
		cnt_success = 0;
		p->func();
		double rate = 1.0 * cnt_success / cnt * 100;
		if (cnt == cnt_success) {
			printf(GREEN("[") BLUE("%8.2lf%%  "), rate);
		} else {
			printf(GREEN("[") RED("%8.2lf%%  "), rate);
		}
		printf(GREEN("] ") "total : %d  success : %d\n", cnt, cnt_success);
	}
	*/

	return 0;
}

void add_func(funcp func, const char *str) {
	struct Function *temp = (struct Function *)calloc(1, sizeof(struct Function));
	temp->func = func;
	temp->name = strdup(str);
	func_tail->p.next = &(temp->p);
	func_tail = temp;

	/*
	node *p = (node *)malloc(sizeof(node));
	tail->next = p;
	p->func = func; 
	p->name = strdup(str); 
	p->next = NULL;
	tail = p;
	*/
	return ;
}
