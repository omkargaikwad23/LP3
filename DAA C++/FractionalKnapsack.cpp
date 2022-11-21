#include<iostream>
#include<algorithm>
/*
Given weights and values of n items, we need to put these items in a knapsack of capacity W to get the maximum total value in the knapsack.
Examples >>
Input: Items as (value, weight) pairs arr[] = {{60, 10}, {100, 20}, {120, 30}} Knapsack Capacity, W = 50;
Output: Maximum possible value = 240 by taking items of weight 10 and 20 kg and 2/3 fraction of 30 kg. Hence total price will be 60+100+(2/3)(120) = 240
*/

using namespace std;

// Structure for an item which stores weight and corresponding value of Item
struct Item
{
    //data members
    int value;
    int weight;

    // Constructor use kiya to automatixally initialise whenever class/struct is created
    Item(int v, int w)
    {
        value = v;
        weight = w;
    }
};

bool cmp(struct Item a, struct Item b)
{
    double ratio_1 = (double)a.value / (double)a.weight;  
    double ratio_2 = (double)b.value / (double)b.weight;  
    return ratio_1 > ratio_2;
}

double fractionalKnapsack(int W, struct Item arr[], int n)
{
    //sorting Item on basis of ratio using 3rd argument in sort()
    sort(arr, arr + n, cmp);

    cout << "\nValues sorted as per ratio\n";
    for (int i = 0; i < n; i++)
    {
        cout << "\n";
        cout << arr[i].value << "  " << arr[i].weight << " : " << ((double)arr[i].value / arr[i].weight);
    }


    int curWeight = 0;       
    double finalvalue = 0.0;

    //Loop through all Items one by one
    for (int i = 0; i < n; i++)
    {
        // If adding Item won't overflow, add it completely
        if ((curWeight + arr[i].weight) <= W)
        {
            curWeight = curWeight + arr[i].weight;
            finalvalue = finalvalue + arr[i].value;
        }
        else
        {
            int remaining = W - curWeight;
            finalvalue += arr[i].value * ((double)remaining / (double)arr[i].weight);
            break;
        }
    }
    return finalvalue;
}

int main()
{
    int W = 50;
    
    Item arr[] = { { 60, 10 }, { 100, 20 }, { 120, 30 } };
    
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "\nMaximum value we can obtain = "
        << fractionalKnapsack(W, arr, n);

    return 0;
}