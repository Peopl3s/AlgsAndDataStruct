#include <iostream>
#include <cmath>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<std::vector<bool>> recursive_dfs_for_adj_matrix_graph(const std::vector<std::vector<int>> &g, const int &row, const int &col)
{
	static std::vector<std::vector<bool>> visited(g.size(), std::vector<bool>(g.size(),0));
	visited[row][col] = true;
	for (int i = row; i != g.size(); ++i)
	{
		for(int j = col; j != g.size(); ++j)
		{
			if(!visited[i][j])
			{
				dfs(g, i, j);	
			}
		}
	}
	return visited;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<std::vector<bool>> bfs_for_adj_matrix_graph(const std::vector<std::vector<int>> &g, const int &row, const int &col)
{
	static std::queue<std::pair<int,int>> q{};
	static std::vector<std::vector<bool>> visited(g.size(), std::vector<bool>(g.size(),false));
	static std::vector<std::vector<bool>> inque(g.size(), std::vector<bool>(g.size(),false)); 
	
	q.push({row, col});
	inque[row][col] = true;
	
	while (!q.empty())
	{
		auto c = q.front();
		q.pop();
		inque[c.first][c.second] = false;
		visited[c.first][c.second] = true;
		
		for (int i = c.first; i != g.size(); ++i)
		{
			for(int j = c.second; j != g.size(); ++j)
			{
				if(!visited[i][j] && !inque[i][j])
				{
					q.push({i,j});
					inque[i][j] = true;
				}
			}
		}
	}	
	return visited;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
double reverse_polish_notation_result(const std::string &str)
{
	std::stack<double> st{};
	double res{};
	std::stringstream ss{str};
	std::string txt{};
	while(ss >> txt)
	{
		if((txt == "*" || txt == "+" || txt == "-" || txt == "/") && !st.empty())
		{
			int top = st.top();
			st.pop();
			int prev = st.top();
			st.pop();
			if (txt == "*")
			{
				res = top * prev;
			}
			else if(txt == "+")
			{
					res = top + prev;
			}
				else if(txt == "-")
			{
					res = prev - top;
			}
				else if(txt == "/")
			{
					res = prev / top;
			}
			st.push(res);
		} 
		else 
		{
			st.push(std::stod(txt));
		}
	}
	return res;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
bool isBalancedBrackets(const std::string &str)
{
	std::stack<char> st{};
    for(int i = 0; i != str.length(); ++i)
    {
    	if(st.empty())
		{
			st.push(str[i]);	
		} 
		else 
		{
			if((st.top() == '(' && str[i] == ')') || (st.top() == '[' && str[i] == ']') || (st.top() == '{' && str[i] == '}') )
       	 	{
            	st.pop();
        	} 
        	else 
        	{
            	st.push(str[i]);
        	}
    	}
    }
    return st.empty() ? true : false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

constexpr  long double factorial(const int &number) noexcept
{
	if (number < 0) return -1;
	if (number == 0 || number == 1) return 1;
	return number * factorial(number - 1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
constexpr  long double sterling_factorial(const int &number) noexcept
{
	return sqrt(2*M_PI*number)*(pow(number,number)/exp(number));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
constexpr  long double double_factorial(const int &number) noexcept
{
	if (number < 0) return -1;
	if (number == 0 || number == 1) return 1;
	return  (number & 1) ? factorial(number)/(pow(2,(number-1)/2)*factorial((number-1)/2)): pow(2,number/2)*factorial(number/2);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
constexpr long double fibbonachi(const int &number) noexcept
{
    if(number <= 0) return 0;
    if(number == 1) return 1;
    return fibbonachi(number-1)+fibbonachi(number-2);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
constexpr long double fibbonachi_gold(const int &number) noexcept
{
    // ×åðåç çîëîòîå ñå÷åíèå, ôîðìóëà Áèíå
    if(number <= 0) return 0;
    if(number == 1) return 1;
    return floor(pow(((1+sqrt(5))/2),number)/sqrt(5));
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
constexpr bool isPrimeNumber(const int &number) noexcept
{
    if (number < 2) return false;
    if (number == 2 || number == 3) return true;
    else if (!(number & 1)) return false;
    else if (!(number % 3)) return false;
    else if (number < 9) return true;
    else
    {  
        for (int i=5; i<=floor(sqrt(number)); i+=6)
        {
            if (!(number % i)) return false;
            if (!(number % (i+2))) return false;
        }
    }
     return true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

constexpr bool isPolindromNumber(const int &number)
{
    if (number < 10) return true;
    int n{number}, pol{0};
    while (n > 0)
    {
        pol = pol*10 + (n % 10);
        n = n / 10;
    } return number == pol;}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

int* removeItem(int *arr, int size, const int &val, int &newSize)
{
    for(int i = 0; i != size; ++i)
    {
        if(arr[i] == val)
        {
            for(int j=i; j != size-1; ++j)
            {
                arr[j] = arr[j+1];
            }
            --size;
            --i;
        }
    }
   newSize = size;
   return arr;    
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

int* sieveEratosthenes(int* arr, int size, int& newSize)
{
    for(int i = 0; i * i <= size; ++i)
    {
        if (arr[i])
        {
            for(int j = i * i; j <= size; j += i)
            {
                arr[j] = 0;
            } }  }
      return removeItem(arr, size, 0, newSize);}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, unsigned int N>
void bubbleSort(T *arr)
{
    T temp{0};
    for(int i = 0; i != N; ++i)
    {
        for(int j = 0; j != N - i; ++j)
        {
            if(arr[j] > arr[j+1])
            {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned int N>
unsigned int binarySearch(T* arr, T val)
{
    unsigned int left{0}, right{N}, mid{0};
    
    if (!N || val > arr[right] || val < arr[left]) return -1;
    
    while (left < right)
    {
        mid = left + (right-left)/2;
        if (val <= arr[mid]) right = mid;
        else left = mid+1;
    }
    
    return (arr[right] == val)? right : -1;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
unsigned int recursiveBinarySearch(T* arr, unsigned int begin, unsigned int end, int val)
{
    unsigned int left{begin}, right{end}, mid{0};
    
    if (!right || val > arr[right] || val < arr[left] || left > right) return -1;
    
    if (arr[right] == val ) return right;
    else if (arr[left] == val ) return left;

        
    while (left < right)
    {
        mid = left + (right-left)/2;
        if (arr[mid] == val) return mid;
        if (val < arr[mid]) return recursiveBinarySearch (arr, left, mid, val);
        else return recursiveBinarySearch(arr, mid+1, right, val);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

long int gcdEuclid(long int a, long int b)
{
    int c{0};
    while(b)
    {
        c = a % b;
        a = b;
        b = c;
    }
    return abs(a);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
long int recursiveGcdEuclid(long int a, long int b)
{
    return (!b)? abs(a) : recursiveGcdEuclid(b, a % b);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
long int lcm(const long int &a, const long int &b)
{
    return abs(a*b)/gcdEuclid(a,b);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int  largestIncreasingSequence(int* arr, int size, int &start, int &end)
{
    int maxSec{0}, tmpMaxSec{0};
    for(int i = 0; i != size - 1; ++i)
    {
        if (arr[i+1]>arr[i])
        {
            ++tmpMaxSec;
        } 
        else { tmpMaxSec = 0; start = i;}
        
        maxSec = tmpMaxSec > maxSec ? tmpMaxSec : maxSec;
        
    }
    ++maxSec;
    start = start - maxSec + 1;
    end = start + maxSec - 1;
    return maxSec;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
long double fast_pow(const int &base, const int &ind)
{
    return exp(ind*log(base));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
long double fast_pow(int base,  int ind)
{
    if (ind == 0) return 1;
    if (ind == 1) return base;
    if (ind < 0) return 1. / fast_pow(base, -ind);
    long double power{1};
    while( ind )
    {
        if (ind & 1) power *= base;
        base *= base;
        ind /= 2;
    }
    return power;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void merge(T* arr, const int first, const  int last) noexcept
{
    T* buffer = new T[last]{};
    int mid =  (last + first) / 2, leftside = first, rightside = mid + 1;
    for (int j = first; j <= last; ++j)
    {
        if ((leftside <= mid) && (( rightside > last)|| (arr[leftside] < arr[rightside])))
        {
            buffer[j] = arr[leftside];
            ++leftside;
        } else 
        {
            buffer[j] = arr[rightside];
            ++rightside;
        }
    }
        for(int i=first; i != last; ++i)
        {
            arr[i] = buffer[i];
        }
        delete[] buffer;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, typename Func>
void mergeSort(int* arr, Func f, const  int first, const  int last) noexcept
{
    if (last <= first) return;
    mergeSort<T>(arr, f, first, (first + last) / 2);
    mergeSort<T>(arr, f, ((first + last) / 2) + 1, last);
    f(arr, first, last);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
void insertSort(T* a, unsigned int size) noexcept
{
    if (size == 0 || size == 1) return;
    for(int i = 1; i < size; ++i)
    {
        T key = a[i];
        for(int j = i - 1; j>=0; --j)
        {
            if (a[j] < key) break;  a[j+1] = a[j];   a[j] = key;
}    
}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void selectionSort(T* arr, const unsigned int &size)
{
    for(int i = 0; i < size - 1; ++i)
    {
        int min_index = i;
        for(int j = i + 1; j < size; ++j)
        {
            if(arr[j] < arr[min_index]) min_index = j;
            
        }
        T tmp = arr[i];
        arr[i] = arr[min_index];
        arr[min_index] = tmp;
    }  
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
int partition(T* arr, const unsigned int &start, const unsigned int &end)
{
    int point = start;
    for(int i = start; i <= end; ++i)
    {
        std::cout<<"Point "<<point<<" ";
        if(arr[i] <= arr[end])
        {
            int tmp = arr[point];
            arr[point] = arr[i];
            arr[i] = tmp;
            ++point;        
        }
    }
    return point - 1;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void quickSort(T* arr, const unsigned int &start, const unsigned int &end)
{
    if(start >= end) return;
    int pivot = partition(arr, start, end);
    quickSort(arr, start, pivot - 1);
    quickSort(arr, pivot + 1, end);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
long int division(long int dividend, long int divider)
{
    if (divider == 0) throw -1;
    int result{0}, numerator = abs(dividend), denominator = abs(divider);
    while(numerator > 0)
    {
        numerator -= denominator;
        ++result;
    }
    return (dividend > 0 && divider > 0)? result : -result;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
long int multyplay(long int a, long int b)
{
    if (a == 0 || b == 0) return 0;
    int first = abs(a), second = abs(b);
    for (int i = 0; i < second; ++i)
    {
        first += abs(a);
    }
    return (a > 0 && b > 0)? first : -first;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

long int dinamyc_fib(const long int& n)
{
    
    long int MAXN = 100;
    std::vector<long int> cache(MAXN, 0);
    
   if (cache[n] == 0)
   {
        if (n == 1 || n == 2 || n == 0) 
        {
            cache[n] = 1;
        } else 
        {
            cache[n] = dinamyc_fib(n - 1) + dinamyc_fib(n - 2);
        }
    }

    return cache[n];
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
long int d_fib(const long int& n)
{
    long int MAXN = 100;
    long int cache[MAXN];
    cache[0] = cache[1] = 1;
    for(size_t i = 2; i <= n; ++i) cache[i] = cache[i - 1] + cache[i - 2];
    return cache[n];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
long int d_fib(const long int& n)
{
    long int back2 = 0; long int back1 = 1;
    if(n == 0) return 0;
    for(size_t i = 2; i < n; ++i)
    {
        long int next = back1 + back2;
        back2 = back1;
        back1 = next;
    }
    return (back1 + back2);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
}
