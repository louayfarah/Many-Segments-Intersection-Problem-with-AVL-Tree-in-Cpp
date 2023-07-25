//Louay Farah
 
/*
Applications of the line segments intersection problem:
 
One crucial application of the n-line segment intersection
is traffic lines management. In fact, Crossroads
(two roads that meet at the same place) can be visualized
as two intersecting straight lines.
*/
 
#include <bits/stdc++.h>
 
using namespace std;
 
#define ll long long int
#define pb push_back
#define mp make_pair
#define endl "\n"
#define fi first
#define se second
 
const int nx[4] = {0, 0, 1, -1};
const int ny[4] = {1, -1, 0, 0};
 
template <typename T> struct Node {
    T key;
    int height;
    Node<T>* left;
    Node<T>* right;
};
 
/*
Implementation of insert and delete operations
are inspired by "https://www.programiz.com/dsa/avl-tree"
*/
template <typename T> class AvlTree
{
private:
    Node<T>* root = NULL;
 
    //Create a new Node
    //Worst-case time complexity: O(1)
    virtual Node<T>* newNode(T key);
 
    //Calculate the height of node
    //Worst-case time complexity: O(1)
    virtual int height(Node<T>* node);
 
    //Right rotate node y
    //Worst-case time complexity: O(1)
    virtual Node<T>* rightRotate(Node<T>* y);
 
    //Left rotate node x
    //Worst-case time complexity: O(1)
    virtual Node<T>* leftRotate(Node<T>* x);
 
    //Get the balance factor node
    //Worst-case time complexity: O(1)
    virtual int getBalanceFactor(Node<T>* node);
 
    //Insert a node into the tree
    //Worst-case time complexity: O(logN)
    virtual Node<T>* insertNode(Node<T>* node, T key);
 
    //Search for the node with minimum value
    //Worst-case time complexity: O(logN)
    virtual Node<T>* minimum(Node<T>* node);
 
    //Search for the node with maximum value
    //Worst-case time complexity: O(logN)
    virtual Node<T>* maximum(Node<T>* node);
 
    //Delete a node from the tree
    //Worst-case time complexity: O(logN)
    virtual Node<T>* deleteNode(Node<T>* node, T key);
 
    //Search for a node in a tree
    //Worst-case time complexity: O(logN)
    virtual Node<T>* searchNode(Node<T>* node, T key);
 
    //Search for the predecessor of a node, if it exists
    //Worst-case time complexity: O(logN)
    virtual Node<T>* predecessorNode(Node<T>* x, T target);
 
    //Search for the successor of a node, if it exists
    //Worst-case time complexity: O(logN)
    virtual Node<T>* successorNode(Node<T>* x, T target);
 
public:
    //Worst-case time complexity: O(logN)
    virtual void insert(T key);
 
    //Worst-case time complexity: O(logN)
    virtual void erase(T key);
 
    //Worst-case time complexity: O(logN)
    virtual Node<T>* search(T key);
 
    //Worst-case time complexity: O(logN)
    virtual bool exists(T key);
 
    //Worst-case time complexity: O(logN)
    virtual Node<T>* predecessor(T target);
 
    //Worst-case time complexity: O(logN)
    virtual Node<T>* successor(T target);
};
 
template <typename T> Node<T>* AvlTree<T>::newNode(T key)
{
    Node<T>* node = new Node<T>();
 
    node->height = 1;
    node->key = key;
    node->left = NULL;
    node->right = NULL;
 
    return node;
}
 
template <typename T> int AvlTree<T>::height(Node<T>* node)
{
    if (node == NULL)
        return 0;
    return node->height;
}
 
template <typename T> Node<T>* AvlTree<T>::rightRotate(Node<T>* y)
{
    Node<T>* x = y->left;
    Node<T>* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}
 
template <typename T> Node<T>* AvlTree<T>::leftRotate(Node<T>* x)
{
    Node<T>* y = x->right;
    Node<T>* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}
 
template <typename T> int AvlTree<T>::getBalanceFactor(Node<T>* node)
{
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}
 
template <typename T> Node<T>* AvlTree<T>::insertNode(Node<T>* node, T key)
{
    if (node == NULL)
        return (newNode(key));
    if (key < node->key)
        node->left = insertNode(node->left, key);
    else if (key > node->key)
        node->right = insertNode(node->right, key);
    else
    {
        return node;
    }
 
    node->height = 1 + max(height(node->left), height(node->right));
    int balanceFactor = getBalanceFactor(node);
    if (balanceFactor > 1)
    {
        if (key < node->left->key)
        {
            return rightRotate(node);
        }
        else if (key > node->left->key)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }
    if (balanceFactor < -1)
    {
        if (key > node->right->key)
        {
            return leftRotate(node);
        }
        else if (key < node->right->key)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }
    return node;
}
 
template <typename T> Node<T>* AvlTree<T>::minimum(Node<T>* node)
{
    Node<T>* res = node;
    while (res->left != NULL)
        res = res->left;
    return res;
}
 
template <typename T> Node<T>* AvlTree<T>::maximum(Node<T>* node)
{
    Node<T>* res = node;
    while (res->right != NULL)
        res = res->right;
    return res;
}
 
template <typename T> Node<T>* AvlTree<T>::deleteNode(Node<T>* node, T key)
{
    if (node == NULL)
        return node;
    if (key < node->key)
        node->left = deleteNode(node->left, key);
    else if (key > node->key)
        node->right = deleteNode(node->right, key);
    else
    {
        if ((node->left == NULL) || (node->right == NULL))
        {
            Node<T>* temp = node->left ? node->left : node->right;
 
            if (temp == NULL)
            {
                temp = node;
                node = NULL;
            }
            else
            {
                *node = *temp;
            }
        }
        else
        {
            Node<T>* temp = minimum(node->right);
            node->key = temp->key;
            node->right = deleteNode(node->right,temp->key);
        }
    }
 
    if (node == NULL)
        return node;
 
    node->height = 1 + max(height(node->left), height(node->right));
    int balanceFactor = getBalanceFactor(node);
    if (balanceFactor > 1)
    {
        if (getBalanceFactor(node->left) >= 0)
        {
            return rightRotate(node);
        }
        else
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }
    if (balanceFactor < -1)
    {
        if (getBalanceFactor(node->right) <= 0)
        {
            return leftRotate(node);
        }
        else
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }
    return node;
}
 
template <typename T> Node<T>* AvlTree<T>::searchNode(Node<T>* node, T key)
{
    if (node == NULL || key == node->key)
    {
        return node;
    }
 
    if (key < node->key)
    {
        return searchNode(node->left, key);
    }
 
    return searchNode(node->right, key);
}
 
template <typename T> Node<T>* AvlTree<T>::predecessorNode(Node<T>* x, T target)
{
    bool hasChanged = false;
 
    Node<T>* res = x;
 
    while(x != NULL)
    {
        if(x->key < target)
        {
            res = x;
            hasChanged = true;
            x = x->right;
        }
        else
        {
            x = x->left;
        }
    }
 
    if(!hasChanged)
    {
        return NULL;
    }
 
    return res;
}
 
template <typename T> Node<T>* AvlTree<T>::successorNode(Node<T>* x, T target)
{
    bool hasChanged = false;
 
    Node<T>* res = x;
 
    while(x != NULL)
    {
        if(x->key <= target)
        {
            x = x->right;
        }
        else
        {
            res = x;
            hasChanged = true;
            x = x->left;
        }
    }
 
    if(!hasChanged)
    {
        return NULL;
    }
 
    return res;
}
 
template <typename T> void AvlTree<T>::insert(T key)
{
    this->root = AvlTree<T>::insertNode(this->root, key);
}
 
template <typename T> void AvlTree<T>::erase(T key)
{
    this->root = AvlTree<T>::deleteNode(this->root, key);
}
 
template <typename T> Node<T>* AvlTree<T>::search(T key)
{
    return AvlTree<T>::searchNode(this->root, key);
}
 
template <typename T> bool AvlTree<T>::exists(T key)
{
    Node<T>* temp = AvlTree<T>::search(key);
 
    if(temp == NULL)
        return false;
 
    return true;
}
 
template <typename T> Node<T>* AvlTree<T>::predecessor(T target)
{
    return AvlTree<T>::predecessorNode(this->root, target);
}
 
template <typename T> Node<T>* AvlTree<T>::successor(T target)
{
    return AvlTree<T>::successorNode(this->root, target);
}
 
 
 
double epsilon = 1e-8;
 
struct Point
{
    ll x, y;
 
    inline bool operator==(Point p)
    {
        if(x == p.x && y == p.y)
            return true;
        return false;
    }
 
};
 
struct DoublePoint
{
    double x, y;
 
    inline bool operator==(Point p)
    {
        if(fabs(x-p.x) < epsilon && fabs(y-p.y) < epsilon)
            return true;
        return false;
    }
};
 
struct Segment
{
    Point A, B;
};
 
bool parallelOrCoincident(Segment s1, Segment s2)
{
    ll temp = (s1.A.x - s1.B.x)*(s2.A.y - s2.B.y) - (s1.A.y - s1.B.y)*(s2.A.x - s2.B.x);
 
    return (temp == 0);
}
 
bool cIsBetweenAandB(Point a, Point b, DoublePoint c)
{
    double crossProduct = (c.y-a.y)*double(b.x-a.x)-(c.x-a.x)*double(b.y-a.y);
 
    if(abs(crossProduct) > epsilon)
        return false;
 
 
    double dotProduct = (c.x-a.x)*double(b.x-a.x) + (c.y-a.y)*double(b.y-a.y);
 
    if(dotProduct < 0)
        return false;
 
    double ab2 = double(b.x-a.x)*(b.x-a.x) + double(b.y-a.y)*(b.y-a.y);
 
    if(dotProduct > ab2)
        return false;
 
    return true;
}
 
bool shareEndpoint(Segment s1, Segment s2)
{
    if(s1.A == s2.A || s1.A == s2.B || s1.B == s2.A || s1.B == s2.B)
        return true;
 
    return false;
}
 
bool segmentsIntersect(Segment s1, Segment s2)
{
    if(parallelOrCoincident(s1, s2))
        return false;
 
    Point A = s1.A;
    Point B = s1.B;
    Point C = s2.A;
    Point D = s2.B;
 
    DoublePoint P;
    P.x = double(A.x*B.y - A.y*B.x)*(C.x - D.x) - double(A.x - B.x)*(C.x*D.y - C.y*D.x);
    P.x /= double(A.x - B.x)*(C.y - D.y) - double(A.y - B.y)*(C.x - D.x);
 
    P.y = double(A.x*B.y - A.y*B.x)*(C.y - D.y) - double(A.y - B.y)*(C.x*D.y - C.y*D.x);
    P.y /= double(A.x - B.x)*(C.y - D.y) - double(A.y - B.y)*(C.x - D.x);
 
    if(!(cIsBetweenAandB(A, B, P) && cIsBetweenAandB(C, D, P)))
        return false;
 
 
    /*if(shareEndpoint(s1, s2))
        return false;*/
 
    return true;
}
 
struct SpecialPoint
{
    Point p;
    bool isStarting;
    int index;
 
    SpecialPoint()
    {
        p.x = 1e9;
        p.y = 1e9;
        isStarting = false;
        index = -1;
    };
 
    inline bool operator<(const SpecialPoint& s) const
    {
        if(p.x == s.p.x)
            return p.y < s.p.y;
        return p.x < s.p.x;
    }
 
    inline bool operator<=(const SpecialPoint& s) const
    {
        if(p.x == s.p.x)
            return p.y <= s.p.y;
        return p.x <= s.p.x;
    }
 
    inline bool operator>(const SpecialPoint& s) const
    {
        if(p.x == s.p.x)
            return p.y > s.p.y;
        return p.x > s.p.x;
    }
 
    inline bool operator>=(const SpecialPoint& s) const
    {
        if(p.x == s.p.x)
            return p.y >= s.p.y;
        return p.x >= s.p.x;
    }
 
    inline bool operator==(const SpecialPoint& s) const
    {
        if(p.x == s.p.x && p.y == s.p.y && index == s.index && isStarting == s.isStarting)
            return true;
        return false;
    }
};
 
 
bool compare(SpecialPoint& A, SpecialPoint& B)
{
    return A.p.y < B.p.y;
}
 
template <typename T> int conquer(vector<T>& arr, int lx, int rx, bool(*comparator)(T& A, T& B))
{
    //Choosing the rightmost element as the pivot element
    int pivot = rx;
    int res = lx-1;
 
    for(int i = lx; i<rx; i++)
    {
        if(comparator(arr[i], arr[pivot]))
        {
            res++;
            swap(arr[i], arr[res]);
        }
    }
 
    swap(arr[pivot], arr[res+1]);
 
    return res+1;
}
 
//Average-case time complexity: O(N*logN)
//Worst-case time complexity: O(N^2)
//Quick-sort is in-place
//Quick-sort is not stable
template <typename T> void quick_sort(vector<T>& arr, int lx, int rx, bool(*comparator)(T& A, T& B))
{
    if(lx >= rx)
    {
        return;
    }
 
    //searching for the position of the pivot after partitioning [lx, rx]
    int pivot = conquer<T>(arr, lx, rx, compare);
 
    quick_sort(arr, lx, pivot-1, compare);
    quick_sort(arr, pivot+1, rx, compare);
}
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    int n;
    cin >> n;
 
    vector<Segment> arr(n); //The array that contains the segments
    vector<SpecialPoint> specialPoints; //The array that contains each point along with its status (starting point, ending point) and it segment's index
    vector<int> startOf(n, 0); //The array that indicates whether the first or the second point of the segment i is the starting point for each i in [0, n-1]
 
    for(int i = 0; i<n; i++)
    {
        cin >> arr[i].A.x >> arr[i].A.y >> arr[i].B.x >> arr[i].B.y;
 
        SpecialPoint temp1;
        temp1.p = arr[i].A;
        temp1.index = i;
 
        SpecialPoint temp2;
        temp2.p = arr[i].B;
        temp2.index = i;
 
        if(temp2.p.y < temp1.p.y)
        {
            temp2.isStarting = true;
            temp1.isStarting = false;
            startOf[i] = 2;
        }
        else
        {
            temp2.isStarting = false;
            temp1.isStarting = true;
            startOf[i] = 1;
        }
 
        specialPoints.pb(temp1);
        specialPoints.pb(temp2);
    }
 
 
    /*
    This is the implementation of the naive O(N^2) solution
 
    for(int i = 0; i<n; i++)
    {
        for(int j = i+1; j<n; j++)
        {
            if(segmentsIntersect(arr[i], arr[j]))
            {
                cout << "INTERSECTION" << endl;
                cout << int(arr[i].A.x) << ' ' << int(arr[i].A.y) << ' ' << int(arr[i].B.x) << ' ' << int(arr[i].B.y) << endl;
                cout << int(arr[j].A.x) << ' ' << int(arr[j].A.y) << ' ' << int(arr[j].B.x) << ' ' << int(arr[j].B.y) << endl;
                return 0;
            }
        }
    }
 
    cout << "NO INTERSECTIONS" << endl;
    */
 
    //Sorting the array of augmented points
    quick_sort<SpecialPoint>(specialPoints, 0, 2*n-1, compare);
 
    //The BST for the sweep process
    AvlTree<SpecialPoint> s;
 
    for(int i = 0; i<2*n; i++)
    {
        if(specialPoints[i].isStarting)
        {
            s.insert(specialPoints[i]);
 
            SpecialPoint it = specialPoints[i];
 
            Node<SpecialPoint>* pred = s.predecessor(it);
 
            if(pred != NULL)
            {
                if(segmentsIntersect(arr[it.index], arr[pred->key.index]))
                {
                    cout << "INTERSECTION" << endl;
                    cout << int(arr[it.index].A.x) << ' ' << int(arr[it.index].A.y) << ' ' << int(arr[it.index].B.x) << ' ' << int(arr[it.index].B.y) << endl;
                    cout << int(arr[pred->key.index].A.x) << ' ' << int(arr[pred->key.index].A.y) << ' ' << int(arr[pred->key.index].B.x) << ' ' << int(arr[pred->key.index].B.y) << endl;
                    return 0;
                }
            }
 
            Node<SpecialPoint>* succ = s.successor(it);
 
            if(succ != NULL)
            {
                if(segmentsIntersect(arr[it.index], arr[succ->key.index]))
                {
                    cout << "INTERSECTION" << endl;
                    cout << int(arr[it.index].A.x) << ' ' << int(arr[it.index].A.y) << ' ' << int(arr[it.index].B.x) << ' ' << int(arr[it.index].B.y) << endl;
                    cout << int(arr[succ->key.index].A.x) << ' ' << int(arr[succ->key.index].A.y) << ' ' << int(arr[succ->key.index].B.x) << ' ' << int(arr[succ->key.index].B.y) << endl;
                    return 0;
                }
            }
 
        }
        else
        {
            SpecialPoint temp;
            if(startOf[specialPoints[i].index] == 1)
            {
                temp.p = arr[specialPoints[i].index].A;
                temp.index = specialPoints[i].index;
                temp.isStarting = true;
            }
            else
            {
                temp.p = arr[specialPoints[i].index].B;
                temp.index = specialPoints[i].index;
                temp.isStarting = true;
            }
 
            SpecialPoint it = temp;
 
            Node<SpecialPoint>* pred = s.predecessor(it);
 
            Node<SpecialPoint>* succ = s.successor(it);
 
 
 
            if(pred != NULL && succ != NULL)
            {
                if(segmentsIntersect(arr[pred->key.index], arr[succ->key.index]))
                {
                    cout << "INTERSECTION" << endl;
                    cout << int(arr[pred->key.index].A.x) << ' ' << int(arr[pred->key.index].A.y) << ' ' << int(arr[pred->key.index].B.x) << ' ' << int(arr[pred->key.index].B.y) << endl;
                    cout << int(arr[succ->key.index].A.x) << ' ' << int(arr[succ->key.index].A.y) << ' ' << int(arr[succ->key.index].B.x) << ' ' << int(arr[succ->key.index].B.y) << endl;
                    return 0;
                }
            }
 
            s.erase(temp);
        }
    }
 
    cout << "NO INTERSECTIONS" << endl;
 
    return 0;
}
