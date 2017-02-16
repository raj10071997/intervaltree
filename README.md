#include <bits/stdc++.h>
using namespace std;


struct interval
{
    int low, high;
};
struct node
{
    interval i; 
    int max;
    node *left, *right;
};
node * newNode(interval i)
{
    node *temp = new node;
    temp->i = i;
    temp->max = i.high;
    temp->left = temp->right = NULL;
};
node *insert(node *root, interval i)
{
    if (root == NULL)
        return newNode(i);
    int l = root->i.low;
    if (i.low < l)
        root->left = insert(root->left, i);
    else
        root->right = insert(root->right, i);
    if (root->max < i.high)
        root->max = i.high;
 
    return root;
}


bool doOVerlap(interval i1, interval i2)
{
    if (i1.low <= i2.high && i2.low <= i1.high)
        return true;
    return false;
}
 
//this function search the given interval
interval ovrlpsearch(node *root, interval i)
{
    interval x;
    x.low=-1;
    if (root == NULL) return x;
 
    
    if (doOVerlap((root->i), i))
        return root->i;
 
   
    if (root->left != NULL && root->left->max >= i.low)
        return ovrlpsearch(root->left, i);
 
    
    return ovrlpsearch(root->right, i);
}


int main()
{
    
    int n;
    cout<<"enter number of intervals"<<endl;
    cin>>n;
    cout<<"now enter the intervals"<<endl;;
    interval in;
    node *root = NULL;
    for (int i = 0; i < n; i++)
    {
    	cin>>in.low>>in.high;
        root = insert(root, in);
    }
    interval x;
    cout<<"search your interval"<<endl;
    cin>>x.low>>x.high;
       interval res = ovrlpsearch(root, x);
    if (res.low == -1)
        cout << "\nNo overlapping Interval"<<endl;
    else
        cout << "\noverlaps with [" << res.low << ", " << res.high << "]"<<endl;
   
    return 0;
}
