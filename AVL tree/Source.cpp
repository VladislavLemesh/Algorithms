#include <iostream>

using namespace std;

struct Node
{
	int hour;
	int min;
	int count, bal;
	Node* left;
	Node* right;
};

void create(Node*& p) //создаёт узел
{
	p = NULL;
}

void insert(Node*& p, int hour, int min, bool& h) //вставка узла с заданным ключом 
{
	Node* p1;
	Node* p2;
	while ((hour > 23) || (hour < 0) || (min > 59) || (min < 0))
	{
		cout << "данные введены некорректно, попробуйте снова" << endl;
		cout << "часы - "; cin >> hour;
		cout << "минуты - "; cin >> min;
	}
	if (!p)
	{
		p = new Node;
		p->hour = hour;
		p->min = min;
		p->count = 1;
		p->bal = 0;
		p->left = NULL;
		p->right = NULL;
		h = true;
	}
	else if ((p->hour * 100 + p->min) > (hour * 100 + min))
	{
		insert(p->left, hour, min, h);
		if (h)
		{
			if (p->bal == 1)
			{
				p->bal = 0;
				h = false;
			}
			else if (p->bal == 0)
			{
				p->bal = -1;
			}
			else
			{
				p1 = p->left;
				if (p1->bal == -1)
				{
					p->left = p1->right;
					p1->right = p;
					p->bal = 0; p = p1;
				}
				else
				{
					p2 = p1->right;
					p1->right = p2->left;
					p2->left = p1;
					p->left = p2->right;
					p2->right = p;
					if (p2->bal == -1)
					{
						p->bal = 1;
					}
					else
					{
						p->bal = 0;
					}
					if (p2->bal == 1)
					{
						p1->bal = -1;
					}
					else
					{
						p1->bal = 0;
					}
					p = p2;
				}
				p->bal = 0; h = false;
			}
		}
	}
	else if ((p->hour * 100 + p->min) < (hour * 100 + min))
	{
		insert(p->right, hour, min, h);
		if (h)
		{
			if (p->bal == -1)
			{
				p->bal = 0;
				h = false;
			}
			else if (p->bal == 0)
			{
				p->bal = 1;
			}
			else
			{
				p1 = p->right;
				if (p1->bal == 1)
				{
					p->right = p1->left;
					p1->left = p;
					p->bal = 0;
					p = p1;
				}
				else
				{
					p2 = p1->left;
					p1->left = p2->right;
					p2->right = p1;
					p->right = p2->left;
					p2->left = p;
					if (p2->bal == 1)
					{
						p->bal = -1;
					}
					else
					{
						p->bal = 0;
					}
					if (p2->bal == -1)
					{
						p1->bal = 1;
					}
					else
					{
						p1->bal = 0;
					}
					p = p2;
				}
				p->bal = 0; h = false;
			}
		}
		else p->count++;
	}

}

Node* minRight(Node* p) //поиск минимального справа ключа 
{
	if ((p) && (p->right))
	{
		p = p->right;
		while (p)
		{
			if (p->left)
			{
				p = p->left;
			}
			else
			{
				return p;
				break;
			}
		}
	}
	else
	{
		cout << "Node not found" << endl;
		return NULL;
	}
}

bool found(Node* p, int hour, int min) //поиск узла по заданному ключу
{
	if (p)
	{
		if ((p->hour * 100 + p->min) > (hour * 100 + min))
		{
			found(p->left, hour, min);
		}
		else if ((p->hour * 100 + p->min) < (hour * 100 + min))
		{
			found(p->right, hour, min);
		}
		else
		{
			return true;
		}
	}
	else
	{
		cout << "Node not found" << endl;
		return false;
	}
}

void balanceL(Node*& p, bool& h) //балансировка если правая ветвь перевесила 
{
	Node* p1;
	Node* p2;
	if (p->bal == -1)
	{
		p->bal = 0;
	}
	else if (p->bal == 0)
	{
		p->bal = 1;
		h = false;
	}
	else
	{
		p1 = p->right;
		if (p1->bal >= 0)
		{
			p->right = p1->left;
			p1->left = p;
			if (p1->bal == 0)
			{
				p->bal = 1;
				p1->bal = -1;
				h = false;
			}
			else
			{
				p->bal = 0;
				p1->bal = 0;
			}
			p = p1;
		}
		else
		{
			p2 = p1->left;
			p1->left = p2->right;
			p2->right = p1;
			p->right = p2->left;
			p2->left = p;
			if (p2->bal == 1)
			{
				p->bal = -1;
			}
			else
			{
				p->bal = 0;
			}
			if (p2->bal == -1)
			{
				p1->bal = 1;
			}
			else
			{
				p1->bal = 0;
			}
			p = p2;
			p2->bal = 0;
		}
	}
}

void balanceR(Node*& p, bool& h) //балансировка если левая ветвь перевесила
{
	Node* p1;
	Node* p2;
	if (p->bal == 1)
	{
		p->bal = 0;
	}
	else if (p->bal == 0)
	{
		p->bal = -1;
		h = false;
	}
	else
	{
		p1 = p->left;
		if (p1->bal <= 0)
		{
			p->left = p1->right;
			p1->right = p;
			if (p1->bal == 0)
			{
				p->bal = -1;
				p1->bal = 1;
				h = false;
			}
			else
			{
				p->bal = 0;
				p1->bal = 0;
			}
			p = p1;
		}
		else
		{
			p2 = p1->right;
			p1->right = p2->left;
			p2->left = p1;
			p->left = p2->right;
			p2->right = p;
			if (p2->bal == -1)
			{
				p->bal = 1;
			}
			else
			{
				p->bal = 0;
			}
			if (p2->bal == 1)
			{
				p1->bal = -1;
			}
			else
			{
				p1->bal = 0;
			}
			p = p2;
			p2->bal = 0;
		}
	}
}

void delet(Node*& p, int hour, int min, bool& h) //функция удаляет узел с заданным ключом
{
	Node* q;
	if (!p)
	{
		cout << "key missing" << endl;
	}
	else if ((p->hour * 100 + p->min) > (hour * 100 + min))
	{
		delet(p->left, hour, min, h);
		if (h)
		{
			balanceL(p, h);
		}
	}
	else if ((p->hour * 100 + p->min) < (hour * 100 + min))
	{
		delet(p->right, hour, min, h);
		if (h)
		{
			balanceR(p, h);
		}
	}
	else
	{
		q = p;
		if (!q->right)
		{
			p = q->left;
			h = true;
		}
		else if (!q->left)
		{
			p = q->right;
			h = true;
		}
		else
		{
			q = minRight(q);
			if (q)
			{
				delet(p, q->hour, q->min, h);
				q->left = p->left;
				q->right = p->right;
				p = q;
			}
		}
	}
}

void clear(Node*& p) //очищает дерево
{
	if (p)
	{
		clear(p->left);
		clear(p->right);
		delete[] p;
		p = NULL;
	}
	else
	{
		return;
	}
}


void pr(Node*& p)
{
	if (p)
	{
		cout << p->hour << ":" << p->min << endl;
		pr(p->left);
		pr(p->right);
	}
	else
	{
		return;
	}
}

void obr(Node*& p)
{
	if (p)
	{
		obr(p->left);
		obr(p->right);
		cout << p->hour << ":" << p->min << endl;
	}
	else
	{
		return;
	}
}

void simLR(Node*& p)
{
	if (p)
	{
		simLR(p->left);
		cout << p->hour << ":" << p->min << endl;
		simLR(p->right);
	}
	else
	{
		return;
	}
}

void simRL(Node*& p)
{
	if (p)
	{
		simRL(p->right);
		cout << p->hour << ":" << p->min << endl;
		simRL(p->left);
	}
	else
	{
		return;
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	bool h;
	Node* a;
	create(a);
	insert(a, 0, 59, h);
	insert(a, 5, 2, h);
	insert(a, 3, 3, h);
	insert(a, 0, 0, h);
	insert(a, 6, 6, h);
	insert(a, 8, 4, h);
	insert(a, 23, 7, h);


	cout << found(a, 5, 2) << endl;
}