#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
struct Mat
{
    int sz;
    vector<vector<int>> m;
    Mat(int size = 2)
    {
        sz = size;
        m.resize(sz);
        for (int i = 0; i < sz; i++)
        {
            for (int j = 0; j < sz; j++)
            {
                m[i].push_back(0);
            }
        }
    }

    void identity()
    {
        for (int i = 0; i < sz; i++)
            m[i][i] = 1;
        return;
    }

    Mat operator*(Mat a)
    {
        Mat res(sz);
        for (int i = 0; i < sz; i++)
        {
            for (int j = 0; j < sz; j++)
            {
                for (int k = 0; k < sz; k++)
                {
                    res.m[i][j] += m[i][k] * a.m[k][j];
                    res.m[i][j] %= mod;
                }
            }
        }
        return res;
    }

    Mat operator^(int n)
    {
        Mat res(sz);
        res.identity();

        Mat T(*this);
        while (n)
        {
            if (n & 1)
                res = res * T;
            T = T * T, n >>= 1;
        }
        return res;
    }
};

struct Recurrence
{
private:
    int sz;
    int order;
    Mat *matrix;
    vector<int> b;

public:
    Recurrence(vector<int> coeffience = {1, 1}, vector<int> base = {1, 1}, bool homo = true)
    {
        sz = coeffience.size();
        order = base.size();
        if (homo)
        {
            if (order != sz)
                exit(-1);
        }
        else
        {
            if (order != (sz - 1))
                exit(-1);
        }

        matrix = new Mat(sz);
        for (int i = 0; i < sz; ++i)
            matrix->m[0][i] = coeffience[i];

        for (int i = 1; i < order; ++i)
            matrix->m[i][i - 1] = 1;

        for (int i = order - 1; i >= 0; --i)
            b.push_back(base[i]);

        if (!homo)
        {
            matrix->m[sz - 1][sz - 1] = 1;
            b.push_back(1);
        }
    }

    ~Recurrence()
    {
        delete matrix;
    }

    int nth_element(int n) //* find the nth element
    {
        if (n < 0)
            return (-1);
        else if (n < order)
            return b[n];

        Mat T(*matrix);
        n = (n - order + 1); //~ assumsed element start from 0
        Mat res = T ^ n;

        long long val = 0;
        for (int i = 0; i < sz; ++i)
            val = ((res.m[0][i] * b[i]) % mod + val % mod);
        return (val % mod);
    }
};



