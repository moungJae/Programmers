#include <string>
#include <vector>

using namespace std;

typedef struct node {
	struct node* prev;
	struct node* next;
	int num;
} Node;

Node* head, * pos;
Node* Stack[1000001];
Node dummy[1000001];
int top;
bool visited[1000001];

void set_node(int n, int k) {
	Node* tmp;

	head = &dummy[1000000];
	tmp = head;
	for (int i = 0; i < n; i++) {
		dummy[i].num = i;
		tmp->next = &dummy[i];
		tmp->next->prev = tmp;
		tmp = tmp->next;
	}

	tmp = head;
	for (int i = 0; i <= k; i++) {
		tmp = tmp->next;
	}
	pos = tmp;
}

void go_up(int X) {
	// prev
	while (X--) {
		pos = pos->prev;
	}
}

void go_down(int X) {
	// next
	while (X--) {
		pos = pos->next;
	}
}

void go_delete() {
	if (pos->next) {
		pos->prev->next = pos->next;
		pos->next->prev = pos->prev;
	}
	else {
		pos->prev->next = 0;
	}
	Stack[top++] = pos;
	if (pos->next) pos = pos->next;
	else pos = pos->prev;
}

void go_update() {
	Node* tmp;

	tmp = Stack[--top];
	if (tmp->next) {
		tmp->prev->next = tmp;
		tmp->next->prev = tmp;
	}
	else {
		tmp->prev->next = tmp;
	}
}

string solution(int n, int k, vector<string> cmd) {
	string answer = "";
	int X;

	set_node(n, k);
	for (int i = 0; i < cmd.size(); i++) {
		if (cmd[i][0] == 'U') {
			X = stoi(&cmd[i][2]);
			go_up(X);
		}
		else if (cmd[i][0] == 'D') {
			X = stoi(&cmd[i][2]);
			go_down(X);
		}
		else if (cmd[i][0] == 'C') {
			go_delete();
		}
		else if (cmd[i][0] == 'Z') {
			go_update();
		}
	}

	for (Node* tmp = head->next; tmp != 0; tmp = tmp->next) {
		visited[tmp->num] = true;
	}

	for (int i = 0; i < n; i++) {
		if (visited[i]) answer += 'O';
		else answer += 'X';
	}

	return answer;
}