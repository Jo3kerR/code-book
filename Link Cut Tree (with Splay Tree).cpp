// https://codeforces.com/contest/1681/submission/158504314
// https://codeforces.com/contest/1681/submission/158267779

const int N = 5e5 + 1;

struct Node
{
    int ch[2] = {}, fa = 0, vir = 0, siz = 0;
    bool rev = 0;
} t[N];

int n, q, sta[N], top;

bool nroot(int x) { return x == t[t[x].fa].ch[0] || x == t[t[x].fa].ch[1]; }

void reverse(int x)
{
    swap(t[x].ch[0], t[x].ch[1]);
    t[x].rev ^= 1;
}

void pushup(int x)
{
    t[x].siz = t[t[x].ch[0]].siz + t[t[x].ch[1]].siz + t[x].vir + 1;
}

void rotate(int x)
{
    int y = t[x].fa;
    int z = t[y].fa;
    int k = x == t[y].ch[1];
    if (nroot(y)) t[z].ch[y == t[z].ch[1]] = x;
    t[x].fa = z;
    t[y].ch[k] = t[x].ch[k ^ 1];
    t[t[x].ch[k ^ 1]].fa = y;
    t[x].ch[k ^ 1] = y;
    t[y].fa = x;
    pushup(y);
    pushup(x);
}

void pushdown(int x)
{
    if (t[x].rev)
    {
        reverse(t[x].ch[0]);
        reverse(t[x].ch[1]);
        t[x].rev = false;
    }
}

void Splay(int x)
{
    int u = x;
    sta[++top] = x;
    while (nroot(u)) sta[++top] = u = t[u].fa;
    while (top) pushdown(sta[top--]);
    while (nroot(x))
    {
        int y = t[x].fa;
        int z = t[y].fa;
        if (nroot(y)) (x == t[y].ch[1]) ^ (y == t[z].ch[1]) ? rotate(x) : rotate(y);
        rotate(x);
    }
}

void access(int x)
{
    for (int y = 0; x; x = t[y = x].fa)
    {
        Splay(x);
        t[x].vir += t[t[x].ch[1]].siz;
        t[x].ch[1] = y;
        t[x].vir -= t[t[x].ch[1]].siz;
        pushup(x);
    }
}

void makeroot(int x)
{
    access(x);
    Splay(x);
    reverse(x);
}

void split(int x, int y)
{
    makeroot(x);
    access(y);
    Splay(y);
}

void link(int x, int y)
{
    makeroot(x);
    access(y);
    Splay(y);
    t[x].fa = y;
    t[y].vir += t[x].siz;
}

void cut(int x, int y) {
    split(x, y);
    t[x].fa = t[y].ch[0] = 0;
    pushup(y);
}
