// Z Function
void calculateZFunction(string &s, int *z)
{
    int n = s.size(), l = 1, r = 1;
    FOR(i, 2, n)
    {
        int k = i - l + 1;
        if (r < i || (r >= i && z[k] >= r - i + 1))
        {
            l = i, r = max(r, i - 1);
            while(r < n && s[r] == s[r - l + 1])
                r ++;
            z[i] = r - l + 1;
        }
        else
            z[i] = z[k];
    }
}