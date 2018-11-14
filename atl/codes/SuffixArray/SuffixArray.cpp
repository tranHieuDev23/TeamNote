// Suffix Array and LCP Array
void calculateSuffixArray(string &s, int* sa, int* group, pair< pair<int, int> , int > * data)
{
    int n = s.size();
    FOR(i, 1, n)
        group[i] = s[i - 1];
    for(int length = 1; length <= n; length <<= 1)
    {
        FOR(i, 1, n)
            data[i] = mp(mp(group[i], (i + length > n? -1 : group[i + length])), i);
        sort(data + 1, data + n + 1);
        FOR(i, 1, n)
            group[data[i].S] = group[data[i - 1].S] + (data[i].F != data[i - 1].F);
    }
    FOR(i, 1, n)
        sa[i] = data[i].S;
}

void calculateLCPArray(string &s, int* lcp, int* sa, int* pos)
{
    int n = s.size();
    FOR(i, 1, n)
        pos[sa[i]] = i;
    int result = 0;
    FOR(i, 1, n)
    {
        if (pos[i] == n)
        {
            result = 0;
            continue;
        }
        int j = sa[pos[i] + 1];
        while(i + result <= n && j + result <= n && s[i + result - 1] == s[j + result - 1])
            result ++;
        lcp[pos[i]] = result;
        if (result)
            result --;
    }
}