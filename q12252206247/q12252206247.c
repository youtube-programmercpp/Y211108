#include <stdio.h>
#include <stdlib.h>
#define	MAXBUFSIZE	512
struct stack {
	char   s[MAXBUFSIZE];
	size_t n;
};
void initstack(struct stack* p)
{
	p->s[p->n = 0] = '\0';
}
void push(struct stack* p, char ch)
{
	const size_t new_n = p->n + 1;
	if (new_n < MAXBUFSIZE) {
		p->s[p->n        ] = ch;
		p->s[p->n = new_n] = '\0';
	}
	else {
		fprintf(stderr, "スタックの領域を超えました。\n");
		exit(EXIT_FAILURE);
	}
}
char pop(struct stack* p)
{
	if (p->n) {
		char* const q = &p->s[--p->n];
		const char ch = *q;
		*q = '\0';
		return ch;
	}
	else {
		fprintf(stderr, "スタックの領域を超えました。\n");
		exit(EXIT_FAILURE);
	}
}
int empty(const struct stack *p)
{
	return p->n == 0;
}
int おかしな順番がある(const char* buf)
{
	struct stack s; //構造体によるスタック
	for (initstack(&s)/*スタックを初期化*/;     ;) {
		const char ch = *buf++;
		switch (ch) {
		case '(': 
		case '[': 
		case '{': 
		case '<':
			push(&s, ch);
			continue;
		case '\n':
		case '\0':
			return !empty(&s);
		case ')': if (pop(&s) == '(') continue; else return 1;
		case ']': if (pop(&s) == '[') continue; else return 1;
		case '}': if (pop(&s) == '{') continue; else return 1;
		case '>': if (pop(&s) == '<') continue; else return 1;
		}
	}
}
int main()
{
	char buf[MAXBUFSIZE];
	if (fgets(buf, sizeof(buf), stdin))
		printf("%s\n", おかしな順番がある(buf) ? "NG" : "OK");
}
