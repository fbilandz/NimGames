#include <iostream>
#include <vector>
#include <set>
#include <cmath>
using namespace std;

// constants and helpers for debugging
#define TRACE(x) cerr << #x << " = " << x << endl
#define __ << " " <<
const int MAXGRUNDY = 20;
const double eps = 1e-6;

// Global variables
vector<int> S;
set<vector<int>> Grundy[MAXGRUNDY];
vector<double> Densities;

// Defining all functions
int LNim(vector<int>);
vector<int> substract(vector<int>, int, int);
void output(vector<int>);
void calculateMex();
vector<vector<double>> calculateSth();
void calculateDensities(int);

// Main function
// Requests x, the number of valid moves, and valid moves
// k can be requested too, and roof as well, but they're set because

int main()
{
    int x, k = 1, roof = 10000;
    cin >> x;
    for (int i = 0; i < x; i++)
    {
        int a;
        cin >> a;
        S.push_back(a);
    }

    // cin >> k >> roof;
    if (x == 0)
    {
        for (int i = 1; i <= roof; i++)
            S.push_back(i);
    }

    vector<int> starting;
    for (int i = 0; i < k; i++)
    {
        starting.push_back(roof - 1);
    }

    LNim(starting);
    /*for (auto pos: Grundy[0]){
        output(pos);
    } */
    calculateDensities(roof);
    cout << "\nDENSITIES \n";
    for (auto pos : Densities)
    {
        cout << pos << endl;
    }
    cout << endl << "A" << endl;
    vector<vector<double>> A = calculateSth();
    cout.precision(5);
    for (auto pos1 : A)
    {
        for (auto pos2 : pos1)
        {
            if (pos2 > eps)
                cout << pos2 << " ";
        }
        cout << endl;
    }
    return 0;
}

// Calculating minimum excluded
int calculateMex(const set<int> &futureGrundy)
{
    int mex = 0;
    while (futureGrundy.find(mex) != futureGrundy.end())
    {
        mex++;
    }
    return mex;
}

// Densities of positions
void calculateDensities(int roof)
{
    int totalPoints = roof;
    for (int i = 0; i < MAXGRUNDY; i++)
    {
        Densities.push_back((double)Grundy[i].size() / (double)totalPoints);
    }
}

int LNim(vector<int> pos)
{
    for (int i = 0; i < MAXGRUNDY; i++)
    {
        if (Grundy[i].find(pos) != Grundy[i].end())
        {
            return i;
        }
    }

    set<int> newPosGrundies;
    for (int a = 0; a < (int)pos.size(); a++)
    {
        for (auto mov : S)
        {
            auto newPos = substract(pos, a, mov);
            if (!newPos.empty())
            {
                newPosGrundies.insert(LNim(newPos));
            }
        }
    }

    int mex = calculateMex(newPosGrundies);
    Grundy[mex].insert(pos);
    return mex;
}

vector<int> substract(vector<int> pos, int ind, int mov)
{
    if (pos[ind] < mov)
        return {};
    pos[ind] -= mov;
    return pos;
}

void output(vector<int> pos)
{
    for (auto x : pos)
    {
        cout << x << " ";
    }
    cout << endl;
}

vector<vector<double>> calculateSth()
{
    vector<double> a = Densities;
    vector<vector<double>> A;
    vector<double> b;
    for (unsigned int i = 0; i < a.size(); i++)
    {
        b.push_back(a[i]);
    }
    A.push_back(b);
    for (unsigned int n = 1; n < a.size(); n++)
    {
        b.clear();
        for (unsigned int k = 0; k < A[n - 1].size(); k++)
        {
            double sum = 0;
            for (unsigned int i = 0; i < a.size(); i++)
            {
                sum += a[i] * A[n - 1][i ^ k];
            }
            b.push_back(sum);
        }
        A.push_back(b);
    }
    return A;
}