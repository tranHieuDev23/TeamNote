// Aho-Corasick
struct AhoCorasick
{
    struct Node
    {
        int cnt;
        vector<int> id;
        Node *nextNode, *nextPatternNode, *child[ALPHABET_SIZE];

        Node()
        {
            cnt = 0;
            id = vector<int>();
            nextNode = nextPatternNode = NULL;
            FOR(i, 0, ALPHABET_SIZE - 1)
                child[i] = NULL;
        }
    } root;

    void insertString(const string &s, int id)
    {
        Node *p = &root;
        FOR(i, 0, int(s.size()) - 1)
        {
            int z = encode(s[i]);
            if (p->child[z] == NULL)
                p->child[z] = new Node();
            p = p->child[z];
        }
        p->id.pb(id);
    }

    queue<Node*> q;

    void calculateNode() 
    {
        q.push(&root);
        while(!q.empty())
        {
            Node *p = q.front();
            q.pop();
            FOR(i, 0, ALPHABET_SIZE - 1)
            if (p->child[i] != NULL)
            {
                Node *c = p->child[i];
                Node *f = p->nextNode;
                while(true)
                {
                    if (f == NULL)
                    {
                        c->nextNode = &root;
                        break;
                    }
                    if (f->child[i] != NULL)
                    {
                        c->nextNode = f->child[i];
                        break;
                    }
                    f = f->nextNode;
                }
                if (c->nextNode->id.empty())
                    c->nextPatternNode = c->nextNode->nextPatternNode;
                else
                    c->nextPatternNode = c->nextNode;
                q.push(p->child[i]);
            }
        }
    }

    void query(const string &s)
    {
        Node *p = &root;
        FOR(i, 0, int(s.size()) - 1)
        {
            int z = encode(s[i]);
            while(p != NULL && p->child[z] == NULL)
                p = p->nextNode;
            if (p == NULL)
                p = &root;
            else
            {
                p = p->child[z];
                p->cnt ++;
            }
        }
    }

    stack<Node*> st;

    void pushAnswer(int *ans) 
    {
        q.push(&root);
        while(!q.empty())
        {
            Node *p = q.front();
            q.pop();
            st.push(p);
            FOR(i, 0, ALPHABET_SIZE - 1)
            if (p->child[i] != NULL)
                q.push(p->child[i]);
        }
        while(!st.empty())
        {
            Node *p = st.top();
            st.pop();
            FOR(i, 0, int(p->id.size()) - 1)
                ans[p->id[i]] += p->cnt;
            if (p->nextNode != NULL)
                p->nextNode->cnt += p->cnt;
        }
    }
};