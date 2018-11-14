// Implicit Treap
template <typename T> class Treap
{
    private:
        class TreapNode
        {
            public:
                T value;
                int priority, cnt;
                TreapNode *lc, *rc;

                TreapNode() {}

                TreapNode(T value): value(value)
                {
                    priority = getRandom(1, maxC);
                    cnt = 1;
                    lc = rc = NULL;
                }
        };

        int getCount(TreapNode* node)
        {
            return (node? node->cnt : 0);
        }

        void updateCount(TreapNode* node)
        {
            if (node)
                node->cnt = getCount(node->lc) + getCount(node->rc) + 1;
        }

        TreapNode* merge(TreapNode* l, TreapNode* r)
        {
            if (!l || !r)
                return (l? l : r);
            TreapNode* re = NULL;
            if (l->priority > r->priority)
            {
                l->rc = merge(l->rc, r);
                re = l;
            }
            else
            {
                r->lc = merge(l, r->lc);
                re = r;
            }
            updateCount(re);
            return re;
        }

        void split(TreapNode* node, TreapNode*& l, TreapNode*& r, int pos, int add = 0)
        {
            if (!node)
            {
                l = r = NULL;
                return;
            }
            int currentPos = add + getCount(node->lc);
            if (pos <= currentPos)
            {
                split(node->lc, l, node->lc, pos, add);
                r = node;
            }
            else
            {
                split(node->rc, node->rc, r, pos, currentPos + 1);
                l = node;
            }
            updateCount(node);
        }

        TreapNode* get(TreapNode* node, int pos, int add = 0)
        {
            if (!node)
                return NULL;
            int currentPos = add + getCount(node->lc);
            if (pos == currentPos)
                return node;
            if (pos < currentPos)
                return get(node->lc, pos, add);
            return get(node->rc, pos, currentPos + 1);
        }

        void erase(TreapNode*& node, int pos, int add = 0)
        {
            if (!node)
                return;
            int currentPos = add + getCount(node->lc);
            if (pos == currentPos)
            {
                delete node;
                node = merge(node->lc, node->rc);
            }
            else if (pos < currentPos)
                erase(node->lc, pos, add);
            else
                erase(node->rc, pos, currentPos + 1);
            updateCount(node);
        }

        void print(TreapNode* node)
        {
            if (!node)
                return;
            print(node->lc);
            cout << node->value << ' ';
            print(node->rc);
        }

        TreapNode* root;

    public:
        Treap()
        {
            root = NULL;
        }

        int size()
        {
            return getCount(root);
        }

        void insert(T value, int pos)
        {
            TreapNode *l = NULL, *r = NULL;
            split(root, l, r, pos);
            TreapNode* newItem = new TreapNode(value);
            root = merge(merge(l, newItem), r);
        }

        void insert(T value)
        {
            insert(value, size());
        }

        T get(int pos)
        {
            return get(root, pos)->value;
        }

        void erase(int pos)
        {
            erase(root, pos);
        }

        void print()
        {
            print(root);
            cout << '\n';
        }
};